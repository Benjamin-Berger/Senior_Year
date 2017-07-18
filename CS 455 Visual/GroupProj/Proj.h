#ifndef __PROJECT_
#define __PROJECT_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
// #include <tesseract/baseapi.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace cv;

#define UNASSIGNED 0
#define N 9

class Sudoku{
	private:

	public:
		bool FindUnassignedLocation(vector<vector<int> > &puzzle, int &row, int &col);
		bool isSafe(vector<vector<int> > &puzzle, int row, int col, int num);
		bool sudokuSolve(vector<vector<int> > &puzzle);
		int templateMask(Mat image);
		void createPuzzle(Mat modified_image, vector<vector<int> > &puzzle);
};

#endif //__PROJECT_
