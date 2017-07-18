#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>


int main(int argc, char **argv) {
  using namespace std;
  using namespace cv;
  
  if(argc != 2) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  //Color CV_LOAD_IMAGE_COLOR
  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  //Mat modified_image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat modified_image(original_image.rows, original_image.cols, CV_32FC3);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &original_image;
 
  //Check that the images loaded
  if(!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
  //Create the display window
  namedWindow("Unix Sample Skeleton");

//code starts here

  original_image.convertTo(original_image, CV_32FC3, 1.0/255);
  modified_image.setTo(0);


  float r, g, b, i, s, h, co1, co2;
  for(int y = 0; y < original_image.rows; y++){
    for(int x = 0; x < original_image.cols; x++){

      b = original_image.at<cv::Vec3f>(y,x)[0];
      g = original_image.at<cv::Vec3f>(y,x)[1];
      r = original_image.at<cv::Vec3f>(y,x)[2];

      i = ((r+g+b)/3);
      s = 1 - (min(r, min(g, b))/i);


      co1 = ((r - g) + (r -b))/2;
      co2 = sqrt((r-g)*(r-g) + (r-b)*(g-b));
      h = co1/co2;
      h = acos(h);

      if( b >= g){
        h = 360 - h;
      }
      
      //cout << bw << endl;
      modified_image.at<cv::Vec3f>(y,x)[2] = i;
      modified_image.at<cv::Vec3f>(y,x)[1] = s;
      modified_image.at<cv::Vec3f>(y,x)[0] = h/360;
      // modified_image.data[(y*original_image.cols + x) * 3] = bw * 100;
    }
  }






  
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
        else {
          image = &original_image;
        }
        break;
      default:
        break;
    }
  }
}