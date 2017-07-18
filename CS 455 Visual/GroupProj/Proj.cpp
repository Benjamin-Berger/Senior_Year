#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>
// #include <tesseract/baseapi.h>

using namespace std;
using namespace cv;

#define UNASSIGNED 0
#define N 9


bool FindUnassignedLocation(vector<vector<int> > &puzzle, int &row, int &col);
bool isSafe(vector<vector<int> > &puzzle, int row, int col, int num);
bool sudokuSolve(vector<vector<int> > &puzzle);

int templateMask(Mat image){
  //set up
  Mat imgLrg = Mat(image.rows * 3, image.cols * 3, CV_LOAD_IMAGE_GRAYSCALE);
  for(int y = 0; y < imgLrg.rows; y++){
    for(int x = 0; x < imgLrg.cols; x++){
      imgLrg.at<uchar>(y, x) = 255;
    }
  }

  for(int y = image.rows; y < image.rows * 2; y++){
    for(int x = image.cols; x < image.cols * 2; x++){
      imgLrg.at<uchar>(y, x) = image.at<uchar>(y - image.rows, x - image.cols);
    }
  }


  string place; 
  int confidence;
  int num = 0;
  int best = 0; 
  for(int i = 1; i < 10; i++){
    place = "Templates/Template" + to_string(i) + ".bmp";
    Mat temp = imread(place, CV_LOAD_IMAGE_GRAYSCALE);


    //take out the bs JUST IN CASE it doesnt work

    for(int y = 1 + 10; y < imgLrg.rows - temp.rows - 10; y++){
      for(int x = 1 + 10; x < imgLrg.cols - temp.cols - 10; x++){
        confidence = 0;
        for(int a = 0; a < temp.rows; a++){
          for(int b = 0; b < temp.cols; b++){
            //instead of checking black space it checks all as to more accurately represent numbers
            if(temp.at<uchar>(a, b) == imgLrg.at<uchar>(y + a, x + b)){
              confidence++;
            }
          }
        }
        if(confidence > best){
          best = confidence;
          num = i;
          //cout << best << endl;
        }
        //optimazation: returning when high enough confidence
        if(best >= 3000){
          return num;
        }
      }
    }
    
    temp.release();
  }


    imgLrg.release();

    return num;
}

bool sudokuSolve(vector<vector<int> > &puzzle){
  int row, col;
  if (!FindUnassignedLocation(puzzle, row, col))
     return true;
  for (int num = 1; num <= 9; num++)
  {
      if (isSafe(puzzle, row, col, num))
      {
          puzzle[row][col] = num;
          if (sudokuSolve(puzzle))
              return true;
          puzzle[row][col] = 0;
      }
  }
  return false;
}


/* Searches the grid to find an entry that is still unassigned. */
bool FindUnassignedLocation(vector<vector<int> > &puzzle, int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (puzzle[row][col] == 0)
                return true;
    return false;
}


/* Returns whether any assigned entry n the specified row matches 
   the given number. */
bool UsedInRow(vector<vector<int> > &puzzle, int row, int num)
{
    for (int col = 0; col < N; col++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry in the specified column matches 
   the given number. */
bool UsedInCol(vector<vector<int> > &puzzle, int col, int num)
{
    for (int row = 0; row < N; row++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches 
   the given number. */
bool UsedInBox(vector<vector<int> > &puzzle, int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (puzzle[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

/* Returns whether it will be legal to assign num to the given row,col location. 
 */
bool isSafe(vector<vector<int> > &puzzle, int row, int col, int num)
{
    return !UsedInRow(puzzle, row, num) && !UsedInCol(puzzle, col, num) &&
           !UsedInBox(puzzle, row - row % 3 , col - col % 3, num);
}

/* print grid  */
void printGrid(vector<vector<int> > &puzzle)
{
  cout << endl;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout<<puzzle[row][col]<<"  ";
        cout<<endl;
    }
}


void createPuzzle(Mat modified_image, vector<vector<int> > &puzzle){
  vector<int> line;



  //Mat *test = &numberBlock;
  //bool testLoop = true;
  int num;
  bool found;
  for(int i = 0; i < 9; i++){
    line.clear();
    for(int j = 0; j < 9; j++){
      //imshow("TEST", *test);
      //testLoop = true;
      found = false;
      num = 0;
      Rect region(10 + (j* 75), 15 + (i* 71), 55, 55);
      Mat numberBlock = modified_image(region);
                  
      for(int y = 0; y < numberBlock.rows; y++){
        for(int x = 0; x < numberBlock.cols; x++){
          if(numberBlock.at<uchar>(y, x) <= 50){
            numberBlock.at<uchar>(y, x) = 0;
            found = true;
          } else { 
            numberBlock.at<uchar>(y, x) = 255;
          }
        }
      }

      if(found){
        num = templateMask(numberBlock);
      }

      line.push_back(num);
      

      // while(testLoop){
      //   switch(cvWaitKey(15)){
      //     case 32:
      //       test = &numberBlock;
      //       cout << i << " " << j << " " << num << endl;
      //       testLoop = false;
      //       break;
      //   }
      // }
      
      cout << num << " ";
      // cout << endl;
      numberBlock.release();
    }
    puzzle.push_back(line);
    cout << endl;
  }

}


int main(int argc, char **argv) {

  
  if(argc != 2) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  //Color CV_LOAD_IMAGE_COLOR
  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

  Rect myROI(304, 610, 675, 655);

  Mat modified_image = original_image(myROI);

  Rect ROI2(10, 10, 55, 55);

  Mat numberBlock = modified_image(ROI2);
  Mat numberBlock2 = modified_image(ROI2);

  //nothing
  //Mat test2 = imread("Test2.bmp", CV_LOAD_IMAGE_GRAYSCALE);

// cout << compnum(numberBlock, test) << endl;




  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &modified_image;


 
  //Check that the images loaded
  if(!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
  //Create the display window
  namedWindow("Unix Sample Skeleton");



  vector<vector<int> > puzzle;

  createPuzzle(modified_image, puzzle);


  if (sudokuSolve(puzzle) == true)
        printGrid(puzzle);
  else
      cout<<"No solution exists"<<endl;
  return 0;


  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    moveWindow("Unix Sample Skeleton", 10, 30);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image){
          image = &modified_image;
        }
        else if(image == &modified_image){
          image = &numberBlock;
        }
        else{
          image = &original_image;
        }
        break;
      default:
        break;
    }
  }
}