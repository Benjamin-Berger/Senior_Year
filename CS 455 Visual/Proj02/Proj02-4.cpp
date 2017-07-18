#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>



  using namespace std;
  using namespace cv;

void maskMaker(int MAX, float SIG, vector<vector<float> > &mask){
vector<float> line;
int x, y;
float val = 0, val2 = 0, vale = 0, fin = 0; 
for(int i = MAX - 1; i >= 0; i--){
  line.clear();
  for(int j = 0; j < MAX; j++){
    // x = j - MAX/2;
    // y = i - MAX/2;
    // val = (1/sqrt(2*3.14159*SIG*SIG));
    // val *= val;
    // val2 = ((x*x) + (y*y))/(SIG*SIG) - 2;
    // vale = ((x*x) + (y*y))/(2*SIG*SIG);
    // vale = exp(-1 * vale);

    // fin = val*val2*vale;
    // if(SIG == 5) cout << fin << endl;
    // line.push_back(fin);


    x = j - MAX/2;
    y = i - MAX/2;
    val = -1 * (1/(3.14159*(SIG*SIG*SIG*SIG)));
    val2 = (1 - ((x*x + y*y)/(2*(SIG*SIG))));
    vale = exp((-1)*((x*x + y*y)/(2*(SIG*SIG))));





    // page 18
  // val = (x*x + y*y - SIG*SIG)/(SIG*SIG*SIG*SIG);
  // vale = exp((-1)*((x*x + y*y)/(2*SIG*SIG)));
  // val2 = (-1);

  fin = val*val2*vale * 1000;
  line.push_back(fin);


  }
  mask.push_back(line);
  }


}



void lupGaus(int MAX, Mat img, vector<vector<float> > mask, vector<vector<float> > &final){

  auto clamp = [](int value, int m, int M){ return value > M ? M : value < m ? m : value; };


  int v1, v2;
  for(int y = 0; y < img.rows; y++){
    for(int x = 0; x < img.cols; x++){
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
          v1 = (y + i-MAX/2);
          v2 = (x  + j - MAX/2);
          if(v1 < 0){
            v1 = 0;
          }
          if(v2 < 0){
            v2 = 0;
          }
          if(v1 >= img.rows){
            v1 = img.rows - 1;
          }
          if(v2 >= img.cols){
            v2 = img.cols - 1;
          }
        //  cout << v1 << " " << v2 << endl;
          //cout << "here" << endl;
          final[y][x] += img.data[v1*img.cols + v2] * mask[i][j];
        }
      }
      if(MAX == 7)
      final[y][x] = clamp(final[y][x], 0, 255);
    }
  }

if(MAX == 11){
  float big = -9999999, small = 99999999;
  for(int y = 0; y < img.rows; y++){
    for(int x = 0; x < img.cols; x++){
      if(final[y][x] < small){
        small = final[y][x];
      } else if(final[y][x] > big){
        big = final[y][x];
      }
    }
  }

  for(int y = 0; y < img.rows; y++){
    for(int x = 0; x < img.cols; x++){
      final[y][x] = ((final[y][x] - small)*255)/(big-small);
    }
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
  Mat modified_image3 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image4 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &original_image;
  Mat *image2 = &original_image2;
 
  //Check that the images loaded
  if(!original_image.data || !modified_image.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }




vector<vector<float> > test; 
vector<float> temp;
for(int y = 0; y < original_image.rows; y++){
  temp.clear();
  for(int x = 0; x < original_image.cols; x++){
    temp.push_back(0);
  }
  test.push_back(temp);
}

vector<vector<float> > test2; 
for(int y = 0; y < original_image2.rows; y++){
  temp.clear();
  for(int x = 0; x < original_image2.cols; x++){
    temp.push_back(0);
  }
  test2.push_back(temp);
}


//build mask 7*7 sig 1.4
vector<vector<float> > mask7x7;
vector<vector<float> > mask11x11;
maskMaker(7, 1.4, mask7x7);
maskMaker(11, 5, mask11x11);


for(int i = 0; i < 9; i++){
  for(int j = 0; j < 9; j++){
    //cout << mask11x11[i][j] << " ";
  }
  // cout << endl;
}

int MAX = 7;
float num = 0;
for(int i = 0; i < MAX; i++){
  for(int j = 0; j < MAX; j++){
    // cout << mask7x7[i][j] << " ";
    num += mask7x7[i][j];
  }
  // cout << endl;
}

// cout << num << endl;

lupGaus(7, original_image, mask7x7, test);

for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    modified_image.data[y*original_image.cols + x] = test[y][x];
  }
}

lupGaus(7, original_image2, mask7x7, test2);
for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    modified_image2.data[y*original_image2.cols + x] = test2[y][x];
  }
}

lupGaus(11, original_image, mask11x11, test);



for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    modified_image3.data[y*original_image.cols + x] = test[y][x];
  }
}


lupGaus(11, original_image2, mask11x11, test2);



for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    modified_image4.data[y*original_image2.cols + x] = test2[y][x];
  }
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
        else if(image == &modified_image){
          image = &modified_image3;
          image2 = &modified_image4;
        }
        else{
          image = &original_image;
          image2 = &original_image2;
        }
        break;
      default:
        break;
    }
  }
}