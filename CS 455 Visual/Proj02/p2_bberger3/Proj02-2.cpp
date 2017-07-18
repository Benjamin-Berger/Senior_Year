#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>


  using namespace std;
  using namespace cv;

auto clamp = [](int value, int m, int M){ return value > M ? M : value < m ? m : value; };

  void meanImg(Mat img, vector<float> &mean){
    float topL, topM, topR, cenL, cenM, cenR, botL, botM, botR;
    int T, B, L, R;
    for(int y = 0; y < img.rows; y++){
      for(int x = 0; x < img.cols; x++){
        //for(int i = 0; i < 3; i++){
          //for(int j = 0; j < 3; j++){
            T = (y - 1);
            B = (y + 1);
            L = (x - 1);
            R = (x + 1);

            if(T < 0){
              T = 0;
              // cout << x << " " << y << endl;
            }
            if(B > img.rows -1){
              B = img.rows - 1;
                            // cout << x << " " << y << endl;
            }
            if(L < 0){
              L = 0;
                            // cout << x << " " << y<< endl;
            }
            if(R > img.cols - 1){
              R = img.cols - 1;
                            // cout << x << " " << y << endl;
            }

            topL = img.data[(T*img.cols + L)];
            topM = img.data[T*img.cols + x];
            topR = img.data[T*img.cols + R];

            cenL = img.data[y*img.cols + L];
            cenM = img.data[y*img.cols + x];
            cenR = img.data[y*img.cols + R];

            botL = img.data[B*img.cols + L];
            botM = img.data[B*img.cols + x];
            botR = img.data[B*img.cols + R];

            mean.push_back(topL/9 + topM/9 + topR/9 + cenL/9 + cenM/9 + cenR/9 + botL/9 + botM/9 + botR/9);
          //}
        //}
      }
    }


  }





int main(int argc, char **argv) {

  
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

vector<float> img; 
for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    img.push_back(original_image.data[y*original_image.cols + x]);
  }
}

vector<float> img2; 
for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    img2.push_back(original_image2.data[y*original_image2.cols + x]);
  }
}

float k = .5;
vector<float> mean;
vector<float> mean2;
meanImg(original_image, mean);
meanImg(original_image2, mean2);

// for(int i = 0; i < img.size(); i++){
//   mean[i] = img[i] - mean[i];
//  mean[i] *= k;
//  // img[i] += mean[i]; 
//   mean[i]  = clamp(mean[i], 0, 255);
// }

float big = -9999999, small = 99999999;
for(int i = 0; i < img.size(); i++){
    if(mean[i] < small){
      small = mean[i];
    } else if(mean[i] > big){
      big = mean[i];
    }
}

for(int i = 0; i < img.size(); i++){
  mean[i] = ((mean[i] - small)*255)/(big-small);
}


for(int i = 0; i < img.size(); i++){
  // cout << mean[i] << endl;
  mean[i] = img[i] - mean[i];
  mean[i] *= k;
  img[i] += mean[i]; 
}

for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    modified_image.data[y*original_image.cols + x] = img[y*original_image.cols + x];
  }
}




big = -9999999, small = 99999999;
for(int i = 0; i < img.size(); i++){
    if(mean2[i] < small){
      small = mean2[i];
    } else if(mean2[i] > big){
      big = mean2[i];
    }
}
for(int i = 0; i < img2.size(); i++){
  mean2[i] = ((mean2[i] - small)*255)/(big-small);
}


for(int i = 0; i < img2.size(); i++){
  // cout << mean[i] << endl;
  mean2[i] = img2[i] - mean2[i];
  mean2[i] *= k;
  img2[i] += mean2[i]; 
}

for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    modified_image2.data[y*original_image2.cols + x] = img2[y*original_image2.cols + x];
  }
}



    // Mat tmp;
    // cv::GaussianBlur(modified_image, tmp, cv::Size(5,5), 3);
    // cv::addWeighted(tmp, .2, modified_image, 1, 0, modified_image);



  
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