#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>


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
  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &original_image;
 
  //Check that the images loaded
  if(!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }
  
  //Create the display window
  namedWindow("Unix Sample Skeleton");

  vector<int> hist1(256);
  vector<int> hist2(256);
  int num = 0;
  int pixSize = 0;
  int cdfMin;
  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      hist1[original_image.data[y*original_image.cols +x]]++;
      pixSize++;
    }
  }
cout << "Histogram of original image." << endl;
for(int i = 0; i < 256; i++){
  cout << i << ": " << hist1[i] << endl;
}



  for(int i = 0; i < 256; i++){
    if(hist1[i] > 0){
      hist2[i] = num + hist1[i];
      num+= hist1[i];
    }
  }

for(int i = 0; i < 256; i++){
  if(hist2[i] > 0){
    cdfMin = hist2[i];
    break;
  }
}

  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      modified_image.data[y*original_image.cols +x] = round(255*(hist2[original_image.data[y*original_image.cols +x]] - cdfMin)/(pixSize - cdfMin)) ;
    }
  }

  vector<int> hist3(256);
  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      hist3[modified_image.data[y*original_image.cols +x]]++;
    }
  }
  cout << "Histogram of modified image." << endl;
for(int i = 0; i < 256; i++){
  cout << i << ": " << hist3[i] << endl;
}


  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image) image = &modified_image;
        else image = &original_image;
        break;
      default:
        break;
    }
  }
}