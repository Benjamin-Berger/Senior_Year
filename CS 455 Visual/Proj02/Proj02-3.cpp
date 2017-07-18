#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <unordered_set>
#include <iostream>





int main(int argc, char **argv) {
  using namespace std;
  using namespace cv;
  
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


auto clamp = [](int value, int m, int M){ return value > M ? M : value < m ? m : value; };

vector<int> img; 
for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    img.push_back(original_image.data[y*original_image.cols + x]);
  }
}


//using extention 
vector<int> mask1;
int topL, topM, topR, cenL, cenM, cenR, botL, botM, botR;
for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    topL = topM = topR = cenL = cenM = cenR = botL = botM = botR = 0;
    if(x == 0 || x == original_image.cols -1 || y == 0 ||y == original_image.rows -1){ //litteral edge cases
      if(x ==0 && y == 0){ //upper left corner
        topL = img[y*original_image.cols + x] * 1;
        topM = img[y*original_image.cols + x] * 0;
        topR = img[y*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * (-2);

        botL = img[(y+1)*original_image.cols + x] * 1;
        botM = img[(y+1)*original_image.cols + x] * 0;
        botR = img[(y+1)*original_image.cols + x + 1] * (-1);
      } else if(x == 0 && y == original_image.rows - 1){ //lower left corner
        topL = img[(y-1)*original_image.cols + x] * 1;
        topM = img[(y-1)*original_image.cols + x] * 0;
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * (-2);

        botL = img[y*original_image.cols + x] * 1;
        botM = img[y*original_image.cols + x] * 0;
        botR = img[y*original_image.cols + x + 1] * (-1);
      } else if(x == original_image.cols -1 && y == 0){ //upper right corner
        topL = img[y*original_image.cols + x - 1] * 1;
        topM = img[y*original_image.cols + x] * 0;
        topR = img[y*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * (-2);

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 0;
        botR = img[(y+1)*original_image.cols + x] * (-1);
      } else if(x == original_image.cols -1 && y == original_image.rows - 1){ //lower right corner
        topL = img[(y-1)*original_image.cols + x - 1] * 1;
        topM = img[(y-1)*original_image.cols + x] * 0;
        topR = img[(y-1)*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * (-2);

        botL = img[y*original_image.cols + x] * 1;
        botM = img[y*original_image.cols + x] * 0;
        botR = img[y*original_image.cols + x + 1] * (-1);
      } else if(x == 0){ //left edge no corners
        topL = img[(y-1)*original_image.cols + x] * 1;
        topM = img[(y-1)*original_image.cols + x] * 0;
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * (-2);

        botL = img[(y+1)*original_image.cols + x] * 1;
        botM = img[(y+1)*original_image.cols + x] * 0;
        botR = img[(y+1)*original_image.cols + x + 1] * (-1);
      } else if(x == original_image.cols - 1){// right edge no corners
        topL = img[(y-1)*original_image.cols + x - 1] * 1;
        topM = img[(y-1)*original_image.cols + x] * 0;
        topR = img[(y-1)*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * (-2);

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 0;
        botR = img[(y+1)*original_image.cols + x] * (-1);
      } else if(y == 0){ //top edge no corners
        topL = img[y*original_image.cols + x - 1] * 1;
        topM = img[y*original_image.cols + x] * 0;
        topR = img[y*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * (-2);

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 0;
        botR = img[(y+1)*original_image.cols + x + 1] * (-1);
      } else if(y == original_image.rows -1){ //bottom edge no corners
        topL = img[(y-1)*original_image.cols + x - 1] * 1;
        topM = img[(y-1)*original_image.cols + x] * 0;
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 2;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * (-2);

        botL = img[y*original_image.cols + x - 1] * 1;
        botM = img[y*original_image.cols + x] * 0;
        botR = img[y*original_image.cols + x + 1] * (-1);
      }

    } else{
      topL = img[(y-1)*original_image.cols + x - 1] * (-1);
      topM = img[(y-1)*original_image.cols + x] * 0;
      topR = img[(y-1)*original_image.cols + x + 1] * 1;

      cenL = img[y*original_image.cols + x - 1] * (-2);
      cenM = img[y*original_image.cols + x] * 0;
      cenR = img[y*original_image.cols + x + 1] * 2;

      botL = img[(y+1)*original_image.cols + x - 1] * (-1);
      botM = img[(y+1)*original_image.cols + x] * 0;
      botR = img[(y+1)*original_image.cols + x + 1] * 1;
    }

    mask1.push_back(topL + topM + topR + cenL + cenM + cenR + botL + botM + botR);

  }
}

vector<int> mask2;
for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    topL = topM = topR = cenL = cenM = cenR = botL = botM = botR = 0;
    if(x == 0 || x == original_image.cols -1 || y == 0 ||y == original_image.rows -1){ //litteral edge cases
      if(x ==0 && y == 0){ //upper left corner
        topL = img[y*original_image.cols + x] * (-1);
        topM = img[y*original_image.cols + x] * (-2);
        topR = img[y*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * 0;

        botL = img[(y+1)*original_image.cols + x] * 1;
        botM = img[(y+1)*original_image.cols + x] * 2;
        botR = img[(y+1)*original_image.cols + x + 1] * 1;
      } else if(x == 0 && y == original_image.rows - 1){ //lower left corner
        topL = img[(y-1)*original_image.cols + x] * (-1);
        topM = img[(y-1)*original_image.cols + x] * (-2);
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * 0;

        botL = img[y*original_image.cols + x] * 1;
        botM = img[y*original_image.cols + x] * 2;
        botR = img[y*original_image.cols + x + 1] * 1;
      } else if(x == original_image.cols -1 && y == 0){ //upper right corner
        topL = img[y*original_image.cols + x - 1] * (-1);
        topM = img[y*original_image.cols + x] * (-2);
        topR = img[y*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * 0;

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 2;
        botR = img[(y+1)*original_image.cols + x] * 1;
      } else if(x == original_image.cols -1 && y == original_image.rows - 1){ //lower right corner
        topL = img[(y-1)*original_image.cols + x - 1] * (-1);
        topM = img[(y-1)*original_image.cols + x] * (-2);
        topR = img[(y-1)*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * 0;

        botL = img[y*original_image.cols + x] * 1;
        botM = img[y*original_image.cols + x] * 2;
        botR = img[y*original_image.cols + x + 1] * 1;
      } else if(x == 0){ //left edge no corners
        topL = img[(y-1)*original_image.cols + x] * (-1);
        topM = img[(y-1)*original_image.cols + x] * (-2);
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * 0;

        botL = img[(y+1)*original_image.cols + x] * 1;
        botM = img[(y+1)*original_image.cols + x] * 2;
        botR = img[(y+1)*original_image.cols + x + 1] * 1;
      } else if(x == original_image.cols - 1){// right edge no corners
        topL = img[(y-1)*original_image.cols + x - 1] * (-1);
        topM = img[(y-1)*original_image.cols + x] * (-2);
        topR = img[(y-1)*original_image.cols + x] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x] * 0;

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 2;
        botR = img[(y+1)*original_image.cols + x] * 1;
      } else if(y == 0){ //top edge no corners
        topL = img[y*original_image.cols + x - 1] * (-1);
        topM = img[y*original_image.cols + x] * (-2);
        topR = img[y*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * 0;

        botL = img[(y+1)*original_image.cols + x - 1] * 1;
        botM = img[(y+1)*original_image.cols + x] * 2;
        botR = img[(y+1)*original_image.cols + x + 1] * 1;
      } else if(y == original_image.rows -1){ //bottom edge no corners
        topL = img[(y-1)*original_image.cols + x - 1] * (-1);
        topM = img[(y-1)*original_image.cols + x] * (-2);
        topR = img[(y-1)*original_image.cols + x + 1] * (-1);

        cenL = img[y*original_image.cols + x - 1] * 0;
        cenM = img[y*original_image.cols + x] * 0;
        cenR = img[y*original_image.cols + x + 1] * 0;

        botL = img[y*original_image.cols + x - 1] * 1;
        botM = img[y*original_image.cols + x] * 2;
        botR = img[y*original_image.cols + x + 1] * 1;
      }
    } else{
      topL = img[(y-1)*original_image.cols + x - 1] * (-1);
      topM = img[(y-1)*original_image.cols + x] * (-2);
      topR = img[(y-1)*original_image.cols + x + 1] * (-1);

      cenL = img[y*original_image.cols + x - 1] * 0;
      cenM = img[y*original_image.cols + x] * 0;
      cenR = img[y*original_image.cols + x + 1] * 0;

      botL = img[(y+1)*original_image.cols + x - 1] * 1;
      botM = img[(y+1)*original_image.cols + x] * 2;
      botR = img[(y+1)*original_image.cols + x + 1] * 1;
    }

    mask2.push_back(topL + topM + topR + cenL + cenM + cenR + botL + botM + botR);

  }
}

int gx, gy, fin;
for(int y = 0; y < original_image.rows; y++){
  for(int x = 0; x < original_image.cols; x++){
    gx = mask1[y*original_image.cols + x];
    gy = mask2[y*original_image.cols + x];
    fin = (gx +gy)/2;
    //fin = sqrt(gx*gx + gy*gy);
    modified_image.data[y*original_image.cols + x] =  clamp(fin, 0, 255);  //sqrt(gx*gx + gy*gy);
  }
}


////////////////
vector<int> img2; 
for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    img2.push_back(original_image2.data[y*original_image2.cols + x]);
  }
}


//using extention 
vector<int> mask3;
for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    topL = topM = topR = cenL = cenM = cenR = botL = botM = botR = 0;
    if(x == 0 || x == original_image2.cols -1 || y == 0 ||y == original_image2.rows -1){ //litteral edge cases
      if(x ==0 && y == 0){ //upper left corner
        topL = img2[y*original_image2.cols + x] * 1;
        topM = img2[y*original_image2.cols + x] * 0;
        topR = img2[y*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * (-2);

        botL = img2[(y+1)*original_image2.cols + x] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 0;
        botR = img2[(y+1)*original_image2.cols + x + 1] * (-1);
      } else if(x == 0 && y == original_image2.rows - 1){ //lower left corner
        topL = img2[(y-1)*original_image2.cols + x] * 1;
        topM = img2[(y-1)*original_image2.cols + x] * 0;
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * (-2);

        botL = img2[y*original_image2.cols + x] * 1;
        botM = img2[y*original_image2.cols + x] * 0;
        botR = img2[y*original_image2.cols + x + 1] * (-1);
      } else if(x == original_image2.cols -1 && y == 0){ //upper right corner
        topL = img2[y*original_image2.cols + x - 1] * 1;
        topM = img2[y*original_image2.cols + x] * 0;
        topR = img2[y*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * (-2);

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 0;
        botR = img2[(y+1)*original_image2.cols + x] * (-1);
      } else if(x == original_image2.cols -1 && y == original_image2.rows - 1){ //lower right corner
        topL = img2[(y-1)*original_image2.cols + x - 1] * 1;
        topM = img2[(y-1)*original_image2.cols + x] * 0;
        topR = img2[(y-1)*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * (-2);

        botL = img2[y*original_image2.cols + x] * 1;
        botM = img2[y*original_image2.cols + x] * 0;
        botR = img2[y*original_image2.cols + x + 1] * (-1);
      } else if(x == 0){ //left edge no corners
        topL = img2[(y-1)*original_image2.cols + x] * 1;
        topM = img2[(y-1)*original_image2.cols + x] * 0;
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * (-2);

        botL = img2[(y+1)*original_image2.cols + x] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 0;
        botR = img2[(y+1)*original_image2.cols + x + 1] * (-1);
      } else if(x == original_image2.cols - 1){// right edge no corners
        topL = img2[(y-1)*original_image2.cols + x - 1] * 1;
        topM = img2[(y-1)*original_image2.cols + x] * 0;
        topR = img2[(y-1)*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * (-2);

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 0;
        botR = img2[(y+1)*original_image2.cols + x] * (-1);
      } else if(y == 0){ //top edge no corners
        topL = img2[y*original_image2.cols + x - 1] * 1;
        topM = img2[y*original_image2.cols + x] * 0;
        topR = img2[y*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * (-2);

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 0;
        botR = img2[(y+1)*original_image2.cols + x + 1] * (-1);
      } else if(y == original_image2.rows -1){ //bottom edge no corners
        topL = img2[(y-1)*original_image2.cols + x - 1] * 1;
        topM = img2[(y-1)*original_image2.cols + x] * 0;
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 2;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * (-2);

        botL = img2[y*original_image2.cols + x - 1] * 1;
        botM = img2[y*original_image2.cols + x] * 0;
        botR = img2[y*original_image2.cols + x + 1] * (-1);
      }

    } else{
      topL = img2[(y-1)*original_image2.cols + x - 1] * (-1);
      topM = img2[(y-1)*original_image2.cols + x] * 0;
      topR = img2[(y-1)*original_image2.cols + x + 1] * 1;

      cenL = img2[y*original_image2.cols + x - 1] * (-2);
      cenM = img2[y*original_image2.cols + x] * 0;
      cenR = img2[y*original_image2.cols + x + 1] * 2;

      botL = img2[(y+1)*original_image2.cols + x - 1] * (-1);
      botM = img2[(y+1)*original_image2.cols + x] * 0;
      botR = img2[(y+1)*original_image2.cols + x + 1] * 1;
    }

    mask3.push_back(topL + topM + topR + cenL + cenM + cenR + botL + botM + botR);

  }
}

vector<int> mask4;
for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    topL = topM = topR = cenL = cenM = cenR = botL = botM = botR = 0;
    if(x == 0 || x == original_image2.cols -1 || y == 0 ||y == original_image2.rows -1){ //litteral edge cases
      if(x ==0 && y == 0){ //upper left corner
        topL = img2[y*original_image2.cols + x] * (-1);
        topM = img2[y*original_image2.cols + x] * (-2);
        topR = img2[y*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * 0;

        botL = img2[(y+1)*original_image2.cols + x] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 2;
        botR = img2[(y+1)*original_image2.cols + x + 1] * 1;
      } else if(x == 0 && y == original_image2.rows - 1){ //lower left corner
        topL = img2[(y-1)*original_image2.cols + x] * (-1);
        topM = img2[(y-1)*original_image2.cols + x] * (-2);
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * 0;

        botL = img2[y*original_image2.cols + x] * 1;
        botM = img2[y*original_image2.cols + x] * 2;
        botR = img2[y*original_image2.cols + x + 1] * 1;
      } else if(x == original_image2.cols -1 && y == 0){ //upper right corner
        topL = img2[y*original_image2.cols + x - 1] * (-1);
        topM = img2[y*original_image2.cols + x] * (-2);
        topR = img2[y*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * 0;

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 2;
        botR = img2[(y+1)*original_image2.cols + x] * 1;
      } else if(x == original_image2.cols -1 && y == original_image2.rows - 1){ //lower right corner
        topL = img2[(y-1)*original_image2.cols + x - 1] * (-1);
        topM = img2[(y-1)*original_image2.cols + x] * (-2);
        topR = img2[(y-1)*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * 0;

        botL = img2[y*original_image2.cols + x] * 1;
        botM = img2[y*original_image2.cols + x] * 2;
        botR = img2[y*original_image2.cols + x + 1] * 1;
      } else if(x == 0){ //left edge no corners
        topL = img2[(y-1)*original_image2.cols + x] * (-1);
        topM = img2[(y-1)*original_image2.cols + x] * (-2);
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * 0;

        botL = img2[(y+1)*original_image2.cols + x] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 2;
        botR = img2[(y+1)*original_image2.cols + x + 1] * 1;
      } else if(x == original_image2.cols - 1){// right edge no corners
        topL = img2[(y-1)*original_image2.cols + x - 1] * (-1);
        topM = img2[(y-1)*original_image2.cols + x] * (-2);
        topR = img2[(y-1)*original_image2.cols + x] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x] * 0;

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 2;
        botR = img2[(y+1)*original_image2.cols + x] * 1;
      } else if(y == 0){ //top edge no corners
        topL = img2[y*original_image2.cols + x - 1] * (-1);
        topM = img2[y*original_image2.cols + x] * (-2);
        topR = img2[y*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * 0;

        botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
        botM = img2[(y+1)*original_image2.cols + x] * 2;
        botR = img2[(y+1)*original_image2.cols + x + 1] * 1;
      } else if(y == original_image2.rows -1){ //bottom edge no corners
        topL = img2[(y-1)*original_image2.cols + x - 1] * (-1);
        topM = img2[(y-1)*original_image2.cols + x] * (-2);
        topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

        cenL = img2[y*original_image2.cols + x - 1] * 0;
        cenM = img2[y*original_image2.cols + x] * 0;
        cenR = img2[y*original_image2.cols + x + 1] * 0;

        botL = img2[y*original_image2.cols + x - 1] * 1;
        botM = img2[y*original_image2.cols + x] * 2;
        botR = img2[y*original_image2.cols + x + 1] * 1;
      }
    } else{
      topL = img2[(y-1)*original_image2.cols + x - 1] * (-1);
      topM = img2[(y-1)*original_image2.cols + x] * (-2);
      topR = img2[(y-1)*original_image2.cols + x + 1] * (-1);

      cenL = img2[y*original_image2.cols + x - 1] * 0;
      cenM = img2[y*original_image2.cols + x] * 0;
      cenR = img2[y*original_image2.cols + x + 1] * 0;

      botL = img2[(y+1)*original_image2.cols + x - 1] * 1;
      botM = img2[(y+1)*original_image2.cols + x] * 2;
      botR = img2[(y+1)*original_image2.cols + x + 1] * 1;
    }

    mask4.push_back(topL + topM + topR + cenL + cenM + cenR + botL + botM + botR);

  }
}

for(int y = 0; y < original_image2.rows; y++){
  for(int x = 0; x < original_image2.cols; x++){
    gx = mask3[y*original_image2.cols + x];
    gy = mask4[y*original_image2.cols + x];
    fin = (gx +gy)/2;
    //fin = sqrt(gx*gx + gy*gy);
    modified_image2.data[y*original_image2.cols + x] =  clamp(fin, 0, 255);  //sqrt(gx*gx + gy*gy);
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