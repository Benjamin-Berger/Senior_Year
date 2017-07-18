#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <math.h>

  using namespace std;
  using namespace cv;

void get8x8(int x, int y, Mat orig, vector<vector<float> > &hold8x8){
  vector<float> hold8;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(y + i == orig.rows)
        break;
      if(x + j < orig.cols)
        hold8.push_back(orig.at<cv::Vec3f>(y + i, x + j)[2]);
    }
    if(y + i < orig.rows){
      hold8x8.push_back(hold8);
      hold8.clear();
    } else {
      break;
    }
  }
}

void DCT(vector<vector<float> > hold8x8, vector<vector<float> > &DCT8x8){
  int rows = hold8x8.size();
  int cols = hold8x8[0].size();
  vector<float> hold8;

  float point, a1, a2, co1, co2, fin;
  float sum = 0;
  for(int v = 0; v < rows; v++){
    for(int u = 0; u < cols; u++){
      for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){

          point = hold8x8[y][x];

          if(u == 0){
            a1 = sqrt(1.0/8);
          } else {
            a2 = sqrt(2.0/8);
          }
          if(v == 0){
            a2 = sqrt(1.0/8);
          } else {
            a2 = sqrt(2.0/8);
          }

          co1 = (2*x + 1) * u * 3.14159/(2.0 * 8);
          co1 = cos(co1);

          co2 = (2*y + 1) * v * 3.14159/(8.0);
          co2 = cos(co2);

          fin = point * a1 * a2 * co1 * co2;

          sum += fin;
        }
      }
      hold8.push_back(sum);
      sum = 0;
    }
    DCT8x8.push_back(hold8);
    hold8.clear();
  }
}

void stitch(int x, int y, vector<vector<float> > DCT8x8, Mat &modi){
  int rows = DCT8x8.size();
  int cols = DCT8x8[0].size();

  for(int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      //cout << DCT8x8[i][j] << endl;
      modi.at<cv::Vec3f>(y + i, x + j)[2] = DCT8x8[i][j];
    }
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
  Mat original_image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
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
      //modified_image.at<cv::Vec3f>(y,x)[1] = s;
      //modified_image.at<cv::Vec3f>(y,x)[0] = h;
    }
  }


for(int y = 0; y < original_image.rows; y += 8){
  for(int x = 0; x < original_image.cols; x += 8){

    vector<vector<float> > hold8x8;
    vector<vector<float> > DCT8x8;


    get8x8(x, y, original_image, hold8x8);


    DCT(hold8x8, DCT8x8);

    stitch(x, y, DCT8x8, modified_image);


  }
}



vector<vector<float> > test;
vector<vector<float> > test1;
vector<float> hold;
vector<float> hold1;

hold.push_back(10);
hold.push_back(11);
hold.push_back(12);
hold.push_back(11);
hold.push_back(12);
hold.push_back(13);
hold.push_back(12);
hold.push_back(11);
hold.push_back(10);
hold.push_back(-10);
hold.push_back(8);
hold.push_back(-7);
hold.push_back(8);
hold.push_back(-8);
hold.push_back(7);
hold.push_back(-7);
test.push_back(hold);

DCT(test, test1);
// for(int i = 0; i < 1; i++){
//   for(int j = 0; j < 16; j++){
//     cout << test1[i][j] << " ";
//   }
//   cout << endl;
// }


  
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