/*
 * C++ Program to Solve Sudoku Problem using BackTracking
 * http://www.sanfoundry.com/cpp-program-solve-sudoku-problem-backtracking/
 */

#include <opencv2/highgui/highgui.hpp>
#include "Sudoku.h"
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
using std::vector;
using cv::Mat;
using cv::Rect;
using cv::imread;

constexpr const int n = 9;

/* assign values to all unassigned locations for Sudoku solution
 */
bool Sudoku::sudokuSolve(vector<vector<int>>& puzzle) {
  int row, col;
  if (!FindUnassignedLocation(puzzle, row, col))
    return true;
  for (int num = 1; num <= 9; num++) {
    if (isSafe(puzzle, row, col, num)) {
      puzzle[row][col] = num;
      if (sudokuSolve(puzzle))
        return true;
      puzzle[row][col] = 0;
    }
  }
  return false;
}


/* Searches the grid to find an entry that is still unassigned. */
bool Sudoku::FindUnassignedLocation(vector<vector<int>>& puzzle,
                                    int& row,
                                    int& col) {
  for (row = 0; row < n; row++)
    for (col = 0; col < n; col++)
      if (puzzle[row][col] == 0)
        return true;
  return false;
}


/* Returns whether any assigned entry n the specified row matches
   the given number. */
bool Sudoku::UsedInRow(vector<vector<int>>& puzzle, int row, int num) {
  for (int col = 0; col < n; col++)
    if (puzzle[row][col] == num)
      return true;
  return false;
}

/* Returns whether any assigned entry in the specified column matches
   the given number. */
bool Sudoku::UsedInCol(vector<vector<int>>& puzzle, int col, int num) {
  for (int row = 0; row < n; row++)
    if (puzzle[row][col] == num)
      return true;
  return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches
   the given number. */
bool Sudoku::UsedInBox(vector<vector<int>>& puzzle,
                       int boxStartRow,
                       int boxStartCol,
                       int num) {
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (puzzle[row + boxStartRow][col + boxStartCol] == num)
        return true;
  return false;
}

/* Returns whether it will be legal to assign num to the given row,col location.
 */
bool Sudoku::isSafe(vector<vector<int>>& puzzle, int row, int col, int num) {
  return !UsedInRow(puzzle, row, num) && !UsedInCol(puzzle, col, num) &&
         !UsedInBox(puzzle, row - row % 3, col - col % 3, num);
}

/* print grid  */
void Sudoku::printGrid(vector<vector<int>>& puzzle) {
  cout << endl;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++)
      cout << puzzle[row][col] << "  ";
    cout << endl;
  }
}
