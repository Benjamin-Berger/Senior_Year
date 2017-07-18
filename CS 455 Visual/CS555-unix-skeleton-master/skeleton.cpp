#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>

int numCur = 256;
bool con = false;

int lowest(int a, int b, int c, int d, int e) {
  int low = 255;
  if(a < low && a > 0){
    low = a;
  }
  if(b < low && b > 0){
    low = b;
  }
  if(c < low && c > 0){
    low = c;
  }
  if(d < low && d > 0){
    low = d;
  }
  if(e < low && e > 0){
    low = e;
  }
  if(low == 255){
    low = numCur;
  }
  if(!con){
    con = true;
  }

  return low;
}

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
  
  //Replace center third of the image with white
  //This can be replaced with whatever filtering you need to do.

  // size_t offset1 = image->rows/3 * image->step;
  // size_t offset2 = image->rows/3*2 * image->step;
  // for(size_t i = offset1; i < offset2; i++) {
  //   modified_image.data[i] = 255;
  //   //modified_image.at<unsigned char>(x_coord, y_coord) = 255;
  // }


  ////////////////////////////part 1 negative
  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
     //modified_image.at<char>(x,y) = 255- original_image.at<char>(x,y);
     //intensity = original_image.at<uchar>(x,y);
     //modified_image.at<uchar>(x,y) = 255 - intensity;
      modified_image.data[y*original_image.cols +x] = 255 - original_image.data[y*original_image.cols +x];
    }
  }
//////////////////////////////////////////

  ///////////////////////part 1 Histogram
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
// cout << round(255*(hist2[original_image.data[y*original_image.cols +x]] - cdfMin)/pixSize - cdfMin) << endl;
//cout << round((hist2[original_image.data[0]] - cdfMin)/(pixSize-cdfMin)*255) << endl;

  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      modified_image.data[y*original_image.cols +x] = round(255*(hist2[original_image.data[y*original_image.cols +x]] - cdfMin)/(pixSize - cdfMin)) ;
    }
  }

  cout << original_image.type() << endl;
////////////////////////////////////
//////////////////////////////////////////////part 2
  
  threshold(original_image, modified_image, 115, 200, 2);
////////////////////////////////////
  /////////////////////////////////////part 3

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

pixSize=0;
  for(size_t x = 0; x < original_image.cols; x++){
    for(size_t y = 0; y < original_image.rows; y++){
      histogram[original_image.data[y*original_image.cols +x]]++;
      pixSize++;
    }
  }

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
cout << T << endl;


//(2)
threshold(original_image, modified_image, T, 255, 0);

//(3)/(4)
vector<int> hist3;
  for(size_t y = 0; y < original_image.rows; y++){
    for(size_t x = 0; x < original_image.cols; x++){
        hist3.push_back(modified_image.data[y*original_image.cols +x]);
    }
  }


// //first pass
//   int cur, top, bot, left, right, low;
//   for(size_t x = 0; x < original_image.cols; x++){
//     for(size_t y = 0; y < original_image.rows; y++){
//       cur = hist3[y*modified_image.cols + x];
//         if(cur == 255){
//           top = hist3[(y+1)* modified_image.cols + x];
//           bot = hist3[(y-1)*modified_image.cols + x];
//           left = hist3[y*modified_image.cols + x - 1];
//           right = hist3[y*modified_image.cols + x + 1];

//           low = lowest(cur, top, bot, left, right);

//           //cur, top, bot, left, right
//           hist3[y* modified_image.cols + x] = low;
//           if(top > 0){
//           hist3[(y+1)* modified_image.cols + x] = low;
//           if(bot > 0)
//           hist3[(y-1)*modified_image.cols + x] = low;
//           if(left > 0)
//           hist3[(y*modified_image.cols + x - 1)] = low;
//           if(right > 0)
//           hist3[(y*modified_image.cols + x + 1)] = low;
//         }
//     }
//     else if(con){
//       con = false;
//       numCur++;
//     }
//   }
// }
cout << hist3.size() << endl;
  vector<int> states; 
  int cur, top, left;
  for(size_t y = 0; y < original_image.rows; y++){
    for(size_t x = 0; x < original_image.cols; x++){
      cur = hist3[y*modified_image.cols + x];
      if(cur == 255){
        top = hist3[(y-1)* modified_image.cols + x];

        left = hist3[y*modified_image.cols + x - 1];

        if(left > 255 && top <= 255){
          cur = left;
        } else if(top > 255 && left <= 255){
          //cout << "here" << endl;
          cur = top;
        } else if(top > 255 && left > 255){
          if(top < left){
            cur = top;
            states.push_back(top);
            states.push_back(left);
          } else if(left < top){
            cur = left;
            states.push_back(left);
            states.push_back(top);
          }
        } else {
          cur = numCur;
        }
        hist3[y*modified_image.cols + x] = cur;
      } else{
        numCur++;
      }
    }
  }

vector<int> tops;
for(int i = 0; i < states.size(); i++){
  tops.push_back(states[i+1]);
}

sort (tops.begin(), tops.begin()+4); 

for(int i = tops.size() -1; i > 0; i--){
  for(int j = states.size() -1; j > 0; j -= 2){
      if(tops[i] == states[j]){
        for(int p = 0; p < hist3.size(); p++){
          if(hist3[p] == states[j]){
            hist3[p] = states[j-1];
          }
        }
      }
  }
}
/*
unordered_set<int> nums;
vector<int> num1;
for(int i = 0; i < hist3.size(); i++){
  if(hist3[i] > 0 && nums.count(hist3[i]) == 0){
    nums.insert(hist3[i]);
    num1.push_back(hist3[i]);
  }
}

  for(size_t y = 0; y < original_image.rows; y++){
    for(size_t x = 0; x < original_image.cols; x++){
      cout << x << ", " << y << " " << hist3[y*original_image.cols + x] << endl;
    }
  }

for(int i = 0; i < hist3.size(); i++){
  cout << i << ": " <<  hist3[i] << endl;
  //cout << num1[i] << endl;
}

for(int i = 0; i < 45; i++){
  cout << endl;
}
*/
/*
for(int i = states.size() - 1; i > 0; i -=2){
  for(int j = 0; j < hist3.size(); j++){
    if(hist3[j] == states[i]){
      hist3[j] = states[i-1];
    }
  }
}
*/
/*

cout << states[states.size() - 1] << endl;
cout << hist3[0] << endl;




for(int i = 0; i < states.size(); i += 2){
  if(states[i] == 0 || states[i+1] == 0)
  cout << states[i] << " <- " << states[i+1] << endl;
}








*/
  for(size_t y = 0; y < original_image.rows; y++){
    for(size_t x = 0; x < original_image.cols; x++){
      modified_image.data[y*modified_image.cols + x] = hist3[y*modified_image.cols + x];
    }
  }

  /////////////////////////////////////
  
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
