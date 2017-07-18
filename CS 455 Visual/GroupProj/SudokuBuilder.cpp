#include "Sudoku.h"

Sudoku::templateMask(Mat image){
  //set up
  Mat imgLrg = Mat(image.rows * 3, image.cols * 3, CV_LOAD_IMAGE_GRAYSCALE);
  for(int y = 0; y < imgLrg.rows; y++){
    for(int x = 0; x < imgLrg.cols; x++){
      imgLrg.at<uchar>(y, x) = 255;
    }
  }

  for(int y = image.rows; y < image.rows * 2; y++){
    for(int x = image.cols; x < image.cols * 2; x++){
      imgLrg.at<uchar>(y, x) = image.at<uchar>(y - image.rows, x - image.cols);
    }
  }


  string place; 
  int confidence;
  int num = 0;
  int best = 0; 
  for(int i = 1; i < 10; i++){
    place = "Template" + to_string(i) + ".bmp";
    Mat temp = imread(place, CV_LOAD_IMAGE_GRAYSCALE);


    //take out the bs JUST IN CASE it doesnt work

    for(int y = 1 + 10; y < imgLrg.rows - temp.rows - 10; y++){
      for(int x = 1 + 10; x < imgLrg.cols - temp.cols - 10; x++){
        confidence = 0;
        for(int a = 0; a < temp.rows; a++){
          for(int b = 0; b < temp.cols; b++){
            //instead of checking black space it checks all as to more accurately represent numbers
            if(temp.at<uchar>(a, b) == imgLrg.at<uchar>(y + a, x + b)){
              confidence++;
            }
          }
        }
        if(confidence > best){
          best = confidence;
          num = i;
          //cout << best << endl;
        }
        //optimazation: returning when high enough confidence
        if(best >= 3000){
          return num;
        }
      }
    }
    
    temp.release();
  }


    imgLrg.release();

    return num;
}


Sudoku::createPuzzle(Mat modified_image, vector<vector<int> > &puzzle){
  vector<int> line;
  int num;
  bool found;
  for(int i = 0; i < 9; i++){
    line.clear();
    for(int j = 0; j < 9; j++){
      found = false;
      num = 0;
      Rect region(10 + (j* 75), 15 + (i* 71), 55, 55);
      Mat numberBlock = modified_image(region);
                  
      for(int y = 0; y < numberBlock.rows; y++){
        for(int x = 0; x < numberBlock.cols; x++){
          if(numberBlock.at<uchar>(y, x) <= 50){
            numberBlock.at<uchar>(y, x) = 0;
            found = true;
          } else { 
            numberBlock.at<uchar>(y, x) = 255;
          }
        }
      }

      if(found){
        num = templateMask(numberBlock);
      }

      line.push_back(num);
      
      cout << num << " ";
      // cout << endl;
      numberBlock.release();
    }
    puzzle.push_back(line);
    cout << endl;
  }

}