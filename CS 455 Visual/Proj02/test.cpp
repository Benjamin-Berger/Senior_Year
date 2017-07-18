#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>



  using namespace std;
  using namespace cv;

  int main(int argc, char **argv) {

  
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  //Color CV_LOAD_IMAGE_COLOR
  Mat original_image(8, 8, DataType<int>::type, CV_LOAD_IMAGE_GRAYSCALE);
  Mat modified_image(8, 8, DataType<int>::type);
  
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &original_image;
 
  //Check that the images loaded


vector<int> test;

for(int i = 0; i < 11; i++)
test.push_back(4);
test.push_back(48);
for(int i = 0; i < 6; i++)
test.push_back(4);
for(int i = 0; i < 4; i++)
test.push_back(64);
for(int i = 0; i < 3; i++)
test.push_back(4);
test.push_back(17);
test.push_back(64);
test.push_back(64);
test.push_back(96);
test.push_back(64);
for(int i = 0; i < 4; i++)
test.push_back(4);
test.push_back(64);
test.push_back(85);
test.push_back(64);
test.push_back(64);
test.push_back(8);
for(int i = 0; i < 3; i++)
test.push_back(4);
for(int i = 0; i < 4; i++)
test.push_back(64);
for(int i = 0; i < 3; i++)
test.push_back(4);
test.push_back(56);
test.push_back(4);
test.push_back(4);
test.push_back(23);
for(int i = 0; i < 11; i++)
test.push_back(4);

vector<int> img;
vector<int> temp;
// int topL, topM, topR, cenL, cenM, cenR, botL, botM, botR;
// int T, B, L, R;
// for(int y = 0; y < 8; y++){
// 	for(int x = 0; x < 8; x++){
// 		temp.clear();
//             T = (y - 1);
//             B = (y + 1);
//             L = (x - 1);
//             R = (x + 1);

//             if(T < 0){
//               T = 0;
//             }
//             if(B > 7){
//               B = 7;
//             }
//             if(L < 0){
//               L = 0;
//             }
//             if(R > 7){
//               R = 7;
//             }

// 		    topL = test[T*8 + L];
//             topM = test[T*8 + x];
//             topR = test[T*8 + R];

//             cenL = test[y*8 + L];
//             cenM = test[y*8 + x];
//             cenR = test[y*8 + R];

//             botL = test[B*8 + L];
//             botM = test[B*8 + x];
//             botR = test[B*8 + R];

//             temp.push_back(topL);
//             temp.push_back(topM);
//             temp.push_back(topR);
//             temp.push_back(cenL);
//             temp.push_back(cenL);
//             temp.push_back(cenL);
//             temp.push_back(botL);
//             temp.push_back(botL);
//             temp.push_back(botL);

//             sort(temp.begin(), temp.end());


//             img.push_back(temp[4]);
// 	}
// }

// int T1, T2, B1, B2, L1, L2, R1, R2;
// for(int y = 0; y < 8; y++){
// 	for(int x = 0; x < 8; x++){
// 		temp.clear();

//             T1 = (y - 2);
//             T2 = (y - 1);
//             B1 = (y + 2);
//             B2 = (y + 1);
//             L1 = (x - 2);
//             L2 = (x - 1);
//             R1 = (x + 2);
//             R2 = (x + 1);

//             if(T1 < 0){
//               T1 = 0;
//             }
//             if(T2 < 0){
//               T2 = 0;
//             }
//             if(B1 > 7){
//               B1 = 7;
//             }
//             if(B2 > 7){
//               B2 = 7;
//             }
//             if(L1 < 0){
//               L = 0;
//             }
//             if(L2 < 0){
//               L2 = 0;
//             }
//             if(R1 > 7){
//               R1 = 7;
//             }
//             if(R2 > 7){
//               R2 = 7;
//             }

// 		    topL = test[(T1*8 + L1)];

//             topM = test[T2*8 + L2];

//             topR = test[T1*8 + R1];

//             cenL = test[T2*8 + R2];

//             cenM = test[y*8 + x]; //center

//             cenR = test[B2*8 + L2];

//             botL = test[B1*8 + L1];
//             botM = test[B2*8 + R2];

//             botR = test[B1*8 + R1];

//             temp.push_back(topL);
//             temp.push_back(topM);
//             temp.push_back(topR);
//             temp.push_back(cenL);
//             temp.push_back(cenL);
//             temp.push_back(cenL);
//             temp.push_back(botL);
//             temp.push_back(botL);
//             temp.push_back(botL);

//             sort(temp.begin(), temp.end());


//             img[y*8 + x] = temp[4];
// 	}
// }



for(int y = 0; y < 8; y++){
	for(int x = 0; x < 8; x++){
		//modified_image.data[y*8 + x] = img[y*8 + x];
		//cout << img[y*8 + x] << " ";
		original_image.data[y*8 + x] = test[y*8 + x];
		cout << test[y*8 + x] << " ";
	}
	cout << endl;
}

imwrite( "testMED3.bmp", original_image );
//imwrite( "testM.jpg", modified_image );

  //Create the display window
  namedWindow("Unix Sample Skeleton");
  // namedWindow("Unix Sample Skeleton 2");


  
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    // imshow("Unix Sample Skeleton 2", *image2);
    moveWindow("Unix Sample Skeleton", 10, 30);
    // moveWindow("Unix Sample Skeleton 2", original_image.cols + 10, 30);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &original_image){
          image = &modified_image;
          // image2 = &modified_image2;
        }
        else {
          image = &original_image;
          // image2 = &original_image2;
        }
        break;
      default:
        break;
    }
  }
}