#include "Sudoku.h"

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

using cv::Mat;
using cv::Rect;
using cv::imread;

bool Sudoku::threshold(Mat& numberBlock) {
  bool found = false;
  for (int y = 0; y < numberBlock.rows; y++) {
    for (int x = 0; x < numberBlock.cols; x++) {
      if (numberBlock.at<uchar>(y, x) <= 50) {
        numberBlock.at<uchar>(y, x) = 0;
        found = true;
      } else {
        numberBlock.at<uchar>(y, x) = 255;
      }
    }
  }

  return found;
}

// for optimization
vector<int> Sudoku::randomGen() {
  vector<int> randNum(9);
  iota(begin(randNum), end(randNum), 1);
  shuffle(randNum.begin(), randNum.end(), g);
  return randNum;
}

void Sudoku::createPuzzle(Mat modified_image, vector<vector<int>>& puzzle) {
  vector<int> line;
  int num;

  for (int i = 0; i < 9; ++i) {
    line.clear();
    vector<int> randNum = randomGen();
    for (int j = 0; j < 9; ++j) {
      num = 0;
      Rect region(10 + (j * 75), 15 + (i * 71), 55, 55);
      Mat numberBlock = modified_image(region);

      if (threshold(numberBlock))
        num = templateMask(numberBlock, randNum);

      line.push_back(num);

      cout << num << " ";
      numberBlock.release();
    }
    puzzle.push_back(line);
    cout << endl;
  }
}

Mat Sudoku::createLarge(Mat image) {
  Mat imgLrg = Mat(image.rows * 3, image.cols * 3, CV_LOAD_IMAGE_GRAYSCALE);

  for (int y = 0; y < imgLrg.rows; ++y)
    for (int x = 0; x < imgLrg.cols; ++x)
      imgLrg.at<uchar>(y, x) = 255;

  for (int y = image.rows; y < image.rows * 2; ++y)
    for (int x = image.cols; x < image.cols * 2; ++x)
      imgLrg.at<uchar>(y, x) = image.at<uchar>(y - image.rows, x - image.cols);

  return imgLrg;
}


int Sudoku::templateMask(Mat image, vector<int>& randNum) {
  Mat imgLrg = createLarge(image);

  string place;
  int confidence;
  int num = 0;
  int best = 0;

  for (size_t i = 0; i < randNum.size(); i++) {
    place = "Templates/Template" + to_string(randNum[i]) + ".bmp";
    Mat temp = imread(place, CV_LOAD_IMAGE_GRAYSCALE);
    // take out the bs JUST IN CASE it doesnt work

    for (int y = 1 + 40; y < imgLrg.rows - temp.rows - 40; y++) {
      for (int x = 1 + 40; x < imgLrg.cols - temp.cols - 40; x++) {
        confidence = 0;
        for (int a = 0; a < temp.rows; a++) {
          for (int b = 0; b < temp.cols; b++) {
            // instead of checking black space it checks all as to more
            // accurately represent numbers
            if (temp.at<uchar>(a, b) == imgLrg.at<uchar>(y + a, x + b)) {
              confidence++;
            }
          }
        }
        if (confidence > best) {
          best = confidence;
          num = randNum[i];
          // optimazation: returning when high enough confidence
          // also removes a number from the list to be checked
          if (best >= 3000) {
            randNum.erase(randNum.begin() + i);
            return num;
          }
        }
      }
    }
    temp.release();
  }
  imgLrg.release();

  return num;
}

Mat Sudoku::fillPuzzle(vector<vector<int>>& puzzle) {
  Mat fin = imread("Fill/TEST.bmp", CV_LOAD_IMAGE_GRAYSCALE);
  string place;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      place = "Fill/Number" + to_string(puzzle[i][j]) + ".bmp";
      Mat temp = imread(place, CV_LOAD_IMAGE_GRAYSCALE);
      for (int y = 0; y < 55; y++) {
        for (int x = 0; x < 55; x++) {
          fin.at<uchar>(15 + (i * 71) + y, 10 + (j* 75) + x) =
              temp.at<uchar>(y, x);
        }
      }
      temp.release();
    }
  }
  return fin;
}
