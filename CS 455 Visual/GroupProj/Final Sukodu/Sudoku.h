#ifndef __PROJECT_
#define __PROJECT_

#include <opencv3/core/core.hpp>
#include <opencv3/highgui/highgui.hpp>
#include "opencv3/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
// #include <tesseract/baseapi.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;
using namespace cv;

#define UNASSIGNED 0
#define N 9

class Sudoku{
	private:
	  	random_device rd;
	  	
	public:
		bool threshold(Mat &numberBlock);
		vector<int> randomGen();
		int templateMask(Mat image, vector<int> &randNum);
		Mat createLarge(Mat image);
		void createPuzzle(Mat modified_image, vector<vector<int> > &puzzle);
		Mat fillPuzzle(vector<vector<int> > &puzzle);

		bool FindUnassignedLocation(vector<vector<int> > &puzzle, int &row, int &col);
		bool isSafe(vector<vector<int> > &puzzle, int row, int col, int num);
		bool sudokuSolve(vector<vector<int> > &puzzle);
		bool UsedInRow(vector<vector<int> > &puzzle, int row, int num);
		bool UsedInCol(vector<vector<int> > &puzzle, int col, int num);
		bool UsedInBox(vector<vector<int> > &puzzle, int boxStartRow, int boxStartCol, int num);
		void printGrid(vector<vector<int> > &puzzle);
};

#endif //__PROJECT_
