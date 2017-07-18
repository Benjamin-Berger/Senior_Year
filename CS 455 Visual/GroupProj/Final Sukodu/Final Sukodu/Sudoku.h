#ifndef __PROJECT_
#define __PROJECT_

#include <vector>
#include <random>

//#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"

class Sudoku {
public:
  Sudoku() : g{rd()} {}
  void createPuzzle(cv::Mat modified_image,
                    std::vector<std::vector<int>>& puzzle);
  bool sudokuSolve(std::vector<std::vector<int>>& puzzle);
  void printGrid(std::vector<std::vector<int>>& puzzle);
  cv::Mat fillPuzzle(std::vector<std::vector<int>>& puzzle);

private:
  bool threshold(cv::Mat& numberBlock);
  std::vector<int> randomGen();
  int templateMask(cv::Mat image, std::vector<int>& randNum);
  cv::Mat createLarge(cv::Mat image);

  bool FindUnassignedLocation(std::vector<std::vector<int>>& puzzle,
                              int& row,
                              int& col);
  bool isSafe(std::vector<std::vector<int>>& puzzle, int row, int col, int num);

  bool UsedInRow(std::vector<std::vector<int>>& puzzle, int row, int num);
  bool UsedInCol(std::vector<std::vector<int>>& puzzle, int col, int num);
  bool UsedInBox(std::vector<std::vector<int>>& puzzle,
                 int boxStartRow,
                 int boxStartCol,
                 int num);

private:
  std::random_device rd;
  std::mt19937 g;
};

#endif //__PROJECT_
