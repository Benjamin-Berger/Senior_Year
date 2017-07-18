#include "Sudoku.h"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

using std::cout;
using std::endl;
using std::vector;

using cv::Mat;
using cv::Rect;
using cv::imread;
using cv::namedWindow;
using cv::moveWindow;

int main(int argc, char** argv) {

  if (argc != 2) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }

  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat* image = &original_image;

  Rect myROI(304, 610, 675, 655);
  Mat modified_image = original_image(myROI);


  // Check that the images loaded
  if (!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }

  // Create the display window
  namedWindow("Sudoku");


  Sudoku solve;
  vector<vector<int>> puzzle;

  solve.createPuzzle(modified_image, puzzle);

  if (solve.sudokuSolve(puzzle))
    solve.printGrid(puzzle);
  else
    cout << "No solution exists" << endl;
  // return 0;

  Mat fin = solve.fillPuzzle(puzzle);


  // imwrite("COMPLETE.jpg", fin);


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
        } else if(image == &modified_image){
          image = &fin;
        }
        else{
          image = &original_image;
        }
        break;
      default:
        break;
    }
  }

  fin.release();
  image -> release();
  original_image.release();
  modified_image.release();



}
