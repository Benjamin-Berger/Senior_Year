#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>


int main(int argc, char **argv) {
  using namespace std;
  using namespace cv;
  
  if(argc != 3) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  //Color CV_LOAD_IMAGE_COLOR
  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat original_image2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &original_image;
  Mat *image2 = &original_image2;
 
  //Check that the images loaded
  if(!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
  //Create the display window
  namedWindow("Unix Sample Skeleton");
  namedWindow("Unix Sample Skeleton 2");


  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    imshow("Unix Sample Skeleton 2", *image2);
    moveWindow("Unix Sample Skeleton", 10, 30);
    moveWindow("Unix Sample Skeleton 2", original_image.cols + 10, 30);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image){
          image = &modified_image;
          image2 = &modified_image2;
        }
        else {
          image = &original_image;
          image2 = &original_image2;
        }
        break;
      default:
        break;
    }
  }
}