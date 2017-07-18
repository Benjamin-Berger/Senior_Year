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
  //cout << r << endl;
  int test = 0;

  for(int y = 0; y < org.rows; y++){
    for(int x = 0; x < org.cols; x++){
      for(int i = r; i <= -r; i++){
        for(int j = r; j <= -r; j++){
          if(x + j < 0){
            test += 255;
          } else if(x + j >= org.cols){
            test += 255;
          } else if(y + i < 0){
            test += 255;
          } else if(y + i >= org.rows){
            test += 255;
          } else {
            test += org.data[(y + i) * org.cols + (x + j)];
          }
        }
      }
      if(test != 2295){
        mod.data[y*org.cols + x] = 0;
      } else {
        //cout << test << endl;
        mod.data[y*org.cols + x] = 255;
      }
      test = 0;
    }
  }

}


void dilation(int m, Mat org, Mat &mod){

  int r = -(m/2);
  //cout << r << endl;
  int test = 0;

  for(int y = 0; y < org.rows; y++){
    for(int x = 0; x < org.cols; x++){
      for(int i = r; i <= -r; i++){
        for(int j = r; j <= -r; j++){
          if(x + j < 0){
            test += 0;
          } else if(x + j >= org.cols){
            test += 0;
          } else if(y + i < 0){
            test += 0;
          } else if(y + i >= org.rows){
            test += 0;
          } else {
            test += org.data[(y + i) * org.cols + (x + j)];
          }
        }
      }
      if(test == 0){
        mod.data[y*org.cols + x] = 0;
      } else {
        mod.data[y*org.cols + x] = 255;
      }
      test = 0;
    }
  }

}

// void manVec(vector<int> &state, int x, int y){
//   bool found = false; 

//   for(int i = 0; i < state.size(); i +=2){
//     if(state[i] == x){
//       if(state[i+1] == y){
//         found = true;
//       }
//     }
//   }

//   if(!found){
//     state.push_back(x);
//     state.push_back(y);
//   }

// }

// void ordVec(vector<int> &state){
//   vector<int> temp;
//   for(int i = 0; i < state.size(); i +=2){
//     temp.push_back(state[i + 1]);
//   }
//   sort(temp.begin(), temp.end());
//   for(int i = 0; i < temp.size(); i++){
//     // cout << temp[i] << endl;
//   }

// }

// void conComp(Mat &mod){
//   vector<int> states;
//   int top;
//   int left;
//   int cur = 256;
//   int num = 0;
//   for(int y = 0; y < mod.rows; y++){
//     for(int x = 0; x < mod.cols; x++){
//       if(mod.data[y*mod.cols + x] == 255){ //if this is a white pixel
//         if(x == 0){
//           left = 999999999;
//         } else if(y == 0){
//           top = 999999999;
//         } else{
//           top = mod.data[(y -1 ) * mod.cols + x];
//           left = mod.data[y * mod.cols + x - 1];

//          // cout << top << endl;
//           if(top == 0){
//             top = 999999999;
//           } 
//           if(left == 0){
//             left = 999999999;
//           }
//         }
//           if(top < left){
//             if(left != 999999999){
//               manVec(states, top, left);
//             }
//             mod.data[y*mod.cols + x] = char(top);
//           } else if(left < top){
//             if(top != 999999999){
//               manVec(states, left, top);
//             }
//             mod.data[y*mod.cols + x] = char(left);
//           } else {
//             mod.data[y*mod.cols + x] = char(cur);
//           }
//       } else{
//         mod.data[y*mod.cols + x] = 0;
//         cur++;
//       }
//     }
//   }



//   ordVec(states);
// }


// void floodfill(int x, int y, int cur, Mat &img){
//   if(img.data[y*img.cols + x] == 255){
//     img.data[y*img.cols +x] = cur;
//   }

//   try{
//     //is the image to the right connected?
//     if(img.data[y*img.cols + x + 1] == 255){
//       floodfill((x+1), y, cur, img);
//     }
//     //is the image below connected?
//     if(img.data[(y+1)*img.cols +x] == 255){
//       floodfill(x, (y+1), cur, img);
//     }
//   } catch (const out_of_range& e){ //ok we have hit the edge
//     //did we hit the right edge?
//     if(x + 1 != img.cols){
//       floodfill(x +1, y, cur + 1, img);
//     } else {
//       //we hit the right edge, did we also hit the bottm edge?
//       if(y + 1 != img.rows){
//         floodfill(0, y+1, cur + 1, img);
//       }
//     }  
//   }

//   //is this not further connected? 
//   if((img.data[y*img.cols + x + 1] == 0) && (img.data[(y+1)*img.cols +x] == 0)){
//     if(x + 1 != img.cols){
//       floodfill(x +1, y, cur + 1, img);
//     } else {
//       if(y + 1 != img.rows){
//         floodfill(0, y+1, cur + 1, img);
//       }
//     }
//   }
// }




void floodfill2(int x, int y, int label, Mat &m) {
//bounds test
if( x >= m.rows || x < 0 || y >= m.cols || y < 0 ) return;

if(m.data[y*m.cols + x] == 255) m.data[y*m.cols + x] = label;
else return;

floodfill2(x-1,y,label,m);
floodfill2(x,y-1,label,m);
floodfill2(x+1,y,label,m);
floodfill2(x,y+1,label,m);
}

// void floodfill2(int x, int y, int label, Mat &m) {
// //bounds test
//   if( x >= m.rows || x < 0 || y >= m.cols || y < 0 ) return;
//   if(m.data[y*m.cols + x] == 255){
//     m.data[y*m.cols + x] = label;
//     floodfill2(x-1,y,label,m);
//     floodfill2(x,y-1,label,m);
//     floodfill2(x+1,y,label,m);
//     floodfill2(x,y+1,label,m);
//   }else{
//     floodfill2(x+1,y,label + 1,m);
//     floodfill2(x,y+1,label + 1,m);
//   }
// }


// void floodfill2(int x, int y, int label, Mat &m) {
// //bounds test
//   if( x >= m.rows || x < 0 || y >= m.cols || y < 0 ) return;

//   if(m.data[y*m.cols + x] == 255){
//     m.data[y*m.cols + x] = label;
//     floodfill2(x-1,y,label,m);
//     floodfill2(x,y-1,label,m);
//     floodfill2(x+1,y,label,m);
//     floodfill2(x,y+1,label,m);
//   }else{
//     // floodfill2(x+1,y,label + 1,m);
//     // floodfill2(x,y+1,label + 1,m);
//     if(x + 1 != m.cols){
//       floodfill2(x +1, y, label + 1, m);
//     } else {
//       if(y + 1 != m.rows){
//         floodfill2(0, y+1, label + 1, m);
//       }
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
erosion(3, modified_image, modified_image1);
dilation(3, modified_image1, modified_image);

int num = 0;
for(int i = 0; i < modified_image.rows; i++){
  for(int j = 0; j < modified_image.cols; j++){
  //     modified_image.data[i*modified_image.cols + j] /= 255;
  //     cout << modified_image.data[i*modified_image.cols + j] << endl;
    // cout << modified_image.at<char>(i,j) << endl;
  }
}


//conComp(modified_image);
int label = 256;
for(int i = 0; i < modified_image.rows; i++){
  for(int j = 0; j < modified_image.cols; j++){
    if(modified_image.data[i*modified_image.cols + j] == 255){
      floodfill2(j, i, label, modified_image);
      label += 1;
    }
  }
}

// for(int i = 0; i < modified_image.rows; i++){
//   for(int j = 0; j < modified_image.cols; j++){
//     if(modified_image.data[i*modified_image.cols + j] != 0){
//       modified_image.data[i*modified_image.cols + j] -= 100;
//     }
//   }
// }

// for(int i = 0; i < modified_image.rows; i++){
//   for(int j = 0; j < modified_image.cols; j++){
//     if(modified_image.data[i*modified_image.cols + j] > 255 ){
//       modified_image.data[i*modified_image.cols + j] = 100;
//     }
//   }
// }


unordered_set<int> test;
vector<int> test1;
for(int i = 0; i < modified_image.rows; i++){
  for(int j = 0; j < modified_image.cols; j++){
    if(test.count(modified_image.data[i*modified_image.cols + j]) == 0){
      test.insert(modified_image.data[i*modified_image.cols +j]);
      test1.push_back(modified_image.data[i*modified_image.cols +j]);
    }
  }
}
map<int, int> hist;
for(int i = 0; i < test1.size(); i++){
  // cout << test1[i] << endl;
  hist[test1[i]] = 0;
}


for(int i = 0; i < modified_image.rows; i++){
  for(int j = 0; j < modified_image.cols; j++){
    hist[modified_image.data[i*modified_image.cols + j]]++;
  }
}

hist[0] = 0;
int countPigs = 0;
for(int i = 0; i < test1.size(); i++){
  // cout << hist[test1[i]] << endl;
  if(hist[test1[i]] < 1000){
    hist[test1[i]] = 0;
  } else {
    countPigs++;
  }
}
cout << countPigs << endl;



for(int i = 0; i < modified_image.rows; i++){
  for(int j = 0; j < modified_image.cols; j++){
    if(modified_image.data[i*modified_image.cols + j] == 1){
      modified_image.data[i*modified_image.cols + j] = 40;
    } else if(modified_image.data[i*modified_image.cols + j] == 5){
      modified_image.data[i*modified_image.cols + j] = 80;
    } else if(modified_image.data[i*modified_image.cols + j] == 255){
      modified_image.data[i*modified_image.cols + j] = 120;
    } else if(modified_image.data[i*modified_image.cols + j] == 254){
      modified_image.data[i*modified_image.cols + j] = 160;
    } else if(modified_image.data[i*modified_image.cols + j] == 200){
      modified_image.data[i*modified_image.cols + j] = 200;
    } else if(modified_image.data[i*modified_image.cols + j] == 173){
      modified_image.data[i*modified_image.cols + j] = 240;
    } else {
      modified_image.data[i*modified_image.cols + j] = 0;
    }

  }
}





// 0 - 
// 1
// 2 - 
// 3 - 
// 4 - 
// 5
// 255
// 82 - 
// 190 ~
// 134 - 
// 254
// 200
// 252 - 
// 69 - 
// 173
// 139 - 
// 191 - 
// 222 - 
// 223 - 
  
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