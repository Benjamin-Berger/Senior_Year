#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>

  using namespace std;
  using namespace cv;

int i=0;

bool compnum(Mat first, Mat second){
  for(int y = 0; y < first.rows; y++){
    for(int x = 0; x < first.cols; x++){
      if(first.at<uchar>(y, x) != second.at<uchar>(y, x)){
        return false;
      }
    }
  }
    return true;

}


int main(int argc, char **argv) {
    
    int array[9][9];

  Mat original_image = imread("Sudoku003.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  Rect myROI(304, 610, 675, 655);
  Mat modified_image = original_image(myROI);
  Mat binary_image = original_image(myROI);
    Mat binary_image2 = original_image(myROI);
    
    for(int y = 0; y < modified_image.rows; y++){
        for(int x = 0; x < modified_image.cols; x++){
            if(modified_image.at<uchar>(y, x)<150){
                binary_image.at<uchar>(y, x)=0;
            }
            else{
                binary_image.at<uchar>(y, x)=255;
            }
        }
    }
    
    
  Rect ROI2(20, 20, 40, 40);
  Rect ROI3(235, 310, 40, 40);


  Mat numberBlock = binary_image(ROI2);
  Mat numberBlock2 = binary_image(ROI3);
  imshow("  ", numberBlock2);
    int u=-1,v=-1;
    int counter=0;
    for(int x = 20; x < modified_image.rows-8; x=x+70){
        u++;
        v=-1;
        for(int y = 20; y < modified_image.cols; y=y+75){
            v++;
            Rect ROI2(y, x, 40, 40);
            numberBlock = binary_image(ROI2);
            counter=0;
            for(int a = 0; a < numberBlock.rows; a++){
                for(int b = 0; b < numberBlock.cols; b++){
                    if(numberBlock.at<uchar>(a, b)==0){
                        counter++;
                    }
                    
                }
            }
            if(counter<100){
                array[u][v]=0;
                
            }
            else if (counter==96){
                array[u][v]=1;
                
            }
            else if (counter==114){
                array[u][v]=7;
                
            }
            else if (counter==138){
                array[u][v]=3;
                
            }
            else if (counter==143){
                array[u][v]=2;
                
            }
            else if (counter==146){
                array[u][v]=5;
                
            }
            else if (counter==147){
                array[u][v]=6;
                
            }
            else if (counter==148){
                array[u][v]=9;
                
            }
            else if (counter==149){
                array[u][v]=4;
                
            }
            else if (counter==204){
                array[u][v]=8;
                
            }
            else{
                array[u][v]=0;
            }
        }
    }
    for(int y = 0; y < 9; y++){
        cout<<endl;
        for(int x = 0; x < 9; x++){
            cout<<array[y][x]<<" ";
        }
    }
 // Mat test = imread("4.bmp", CV_LOAD_IMAGE_GRAYSCALE);
    //imwrite("7.bmp", numberBlock2 );

  //cout << compnum(numberBlock2, test) << endl;
   /* int counter=0;
    for(int y = 0; y < test.rows; y++){
        for(int x = 0; x < test.cols; x++){
            if(test.at<uchar>(y, x)==0){
                counter++;
            }
           
        }
    }
    cout<<counter;
 */


//imshow("  ", modified_image);
 
    
    waitKey(0);
    return 0;
}


  //Display loop
 /* bool loop = true;
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
  }*/