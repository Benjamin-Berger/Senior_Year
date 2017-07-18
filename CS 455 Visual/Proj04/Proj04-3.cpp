#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <map>

  using namespace std;
  using namespace cv;


void erosion(int m, Mat org, Mat &mod){
  int r = -(m/2);
  int max = 0;
  for(int y = 0; y < org.rows; y++){
    for(int x = 0; x < org.cols; x++){
      for(int i = r; i <= -r; i++){
        for(int j = r; j <= -r; j++){
          if(x + j < 0){
          } else if(x + j >= org.cols){
          } else if(y + i < 0){
          } else if(y + i >= org.rows){
          } else if(max < org.data[(y + i) * org.cols + (x + j)]){
            max = org.data[(y + i) * org.cols + (x + j)];
          }
        }
      }
      mod.data[y*org.cols + x] = max;
      max = 0;
    }
  }
}

void dilation(int m, Mat org, Mat &mod){
  int r = -(m/2);
  int min = 256;
  for(int y = 0; y < org.rows; y++){
    for(int x = 0; x < org.cols; x++){
      for(int i = r; i <= -r; i++){
        for(int j = r; j <= -r; j++){
          if(x + j < 0){
          } else if(x + j >= org.cols){
          } else if(y + i < 0){
          } else if(y + i >= org.rows){
          } else if(min > org.data[(y + i) * org.cols + (x + j)]){
            min = org.data[(y + i) * org.cols + (x + j)];
          }
        }
      }
      mod.data[y*org.cols + x] = min;
      min = 256;
    }
  }
}



// void erosion(int m, Mat org, Mat &mod){

//   int r = -(m/2);
//   //cout << r << endl;
//   int test = 0;

//   for(int y = 0; y < org.rows; y++){
//     for(int x = 0; x < org.cols; x++){
//       for(int i = r; i <= -r; i++){
//         for(int j = r; j <= -r; j++){
//           if(x + j < 0){
//             test += 255;
//           } else if(x + j >= org.cols){
//             test += 255;
//           } else if(y + i < 0){
//             test += 255;
//           } else if(y + i >= org.rows){
//             test += 255;
//           } else {
//             test += org.data[(y + i) * org.cols + (x + j)];
//           }
//         }
//       }
//       if(test != 2295){
//         mod.data[y*org.cols + x] = 0;
//       } else {
//         //cout << test << endl;
//         mod.data[y*org.cols + x] = 255;
//       }
//       test = 0;
//     }
//   }
// }


// void dilation(int m, Mat org, Mat &mod){

//   int r = -(m/2);
//   //cout << r << endl;
//   int test = 0;

//   for(int y = 0; y < org.rows; y++){
//     for(int x = 0; x < org.cols; x++){
//       for(int i = r; i <= -r; i++){
//         for(int j = r; j <= -r; j++){
//           if(x + j < 0){
//             test += 0;
//           } else if(x + j >= org.cols){
//             test += 0;
//           } else if(y + i < 0){
//             test += 0;
//           } else if(y + i >= org.rows){
//             test += 0;
//           } else {
//             test += org.data[(y + i) * org.cols + (x + j)];
//           }
//         }
//       }
//       if(test == 0){
//         mod.data[y*org.cols + x] = 0;
//       } else {
//         mod.data[y*org.cols + x] = 255;
//       }
//       test = 0;
//     }
//   }

// }

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
  Mat modified_image1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image2 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image3 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  
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

//opening operation
//flood fill labeling --- this is recursive. not using this. using connected components

erosion(3, original_image, modified_image2);
dilation(3, original_image, modified_image3);


erosion(3, original_image, modified_image1);
dilation(3, modified_image1, modified_image);




  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image){
          image = &modified_image2;
        } else if(image == &modified_image2){
          image = &modified_image3;
        } else if( image == &modified_image3){
          image = &modified_image;
        }
        else image = &original_image;
        break;
      default:
        break;
    }
  }
}