#include "Sudoku.h"

Sudoku::sudokuSolve(vector<vector<int> > &puzzle){
  int row, col;
  if (!FindUnassignedLocation(puzzle, row, col))
     return true;
  for (int num = 1; num <= 9; num++)
  {
      if (isSafe(puzzle, row, col, num))
      {
          puzzle[row][col] = num;
          if (sudokuSolve(puzzle))
              return true;
          puzzle[row][col] = 0;
      }
  }
  return false;
}


/* Searches the grid to find an entry that is still unassigned. */
Sudoku::FindUnassignedLocation(vector<vector<int> > &puzzle, int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (puzzle[row][col] == 0)
                return true;
    return false;
}


/* Returns whether any assigned entry n the specified row matches 
   the given number. */
Sudoku::UsedInRow(vector<vector<int> > &puzzle, int row, int num)
{
    for (int col = 0; col < N; col++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry in the specified column matches 
   the given number. */
Sudoku::UsedInCol(vector<vector<int> > &puzzle, int col, int num)
{
    for (int row = 0; row < N; row++)
        if (puzzle[row][col] == num)
            return true;
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches 
   the given number. */
Sudoku::UsedInBox(vector<vector<int> > &puzzle, int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (puzzle[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

/* Returns whether it will be legal to assign num to the given row,col location. 
 */
Sudoku::isSafe(vector<vector<int> > &puzzle, int row, int col, int num)
{
    return !UsedInRow(puzzle, row, num) && !UsedInCol(puzzle, col, num) &&
           !UsedInBox(puzzle, row - row % 3 , col - col % 3, num);
}

/* print grid  */
Sudoku::printGrid(vector<vector<int> > &puzzle)
{
  cout << endl;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout<<puzzle[row][col]<<"  ";
        cout<<endl;
    }
}
