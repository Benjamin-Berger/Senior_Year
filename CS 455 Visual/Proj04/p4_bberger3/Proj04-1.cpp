#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <map>

  using namespace std;
  using namespace cv;


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


//Otsu method for creating a Binary image
//code from http://www.dandiggins.co.uk/arlib-9.html
float  w = 0;                // first order cumulative
float  u = 0;                // second order cumulative
float  uT = 0;               // total mean level

int    k = 255;              // maximum histogram index
int    T = 0;        // optimal threshold value

float  histNormalized[256];  // normalized histogram values

float  work1, work2;    // working variables
double work3 = 0.0;
float histogram[256];  

 int pixSize=0;
  for(size_t y = 0; y < original_image.rows; y++){
    for(size_t x = 0; x < original_image.cols; x++){
      histogram[original_image.data[y*original_image.cols +x]]++;
      pixSize++;
    }
  }
///////////////////////////////////////


  // Create normalised histogram values
// (size=image width * image height)
for (int I=1; I<=k; I++) 
histNormalized[I-1] = histogram[I-1]/(float)pixSize;


// Calculate total mean level
for (int I=1; I<=k; I++) 
uT+=(I*histNormalized[I-1]);


// Find optimal threshold value
for (int I=1; I<k; I++) {
    w+=histNormalized[I-1];
    u+=(I*histNormalized[I-1]);
    work1 = (uT * w - u);
    work2 = (work1 * work1) / ( w * (1.0f-w) );
    if (work2>work3) work3=work2;
}

// Convert the final value to an integer
//(1)
T = (int)sqrt(work3);
//cout << T << endl;

//hard coded my own Threshold
T = 200;

  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      if(original_image.data[y*original_image.cols + x] <= T){
        modified_image.data[y*original_image.cols + x] = 0;
      } else { 
        modified_image.data[y*original_image.cols + x] = 255;
      }
    }
  }

//dont use this!
//threshold(original_image, modified_image, T, 255, 0);


/////////////////********* AT THIS POINT I HAVE A BINARY REPRESENTATION **********///////////////////////////////


  
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