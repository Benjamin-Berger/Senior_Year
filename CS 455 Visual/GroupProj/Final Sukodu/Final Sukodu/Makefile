COMPILER = g++
FLAGS = -g3 -std=c++11 -Wall -pedantic -Wextra
EXECUTABLE = Proj
OBJECTS = Driver.o SudokuBuilder.o SudokuSolver.o

all: Driver.o SudokuBuilder.o SudokuSolver.o
	$(COMPILER) $(FLAGS) `pkg-config --cflags opencv` ${OBJECTS} `pkg-config --libs opencv` -o $(EXECUTABLE)

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

SudokuBuilder.o: SudokuBuilder.cpp
	$(COMPILER) $(FLAGS) -c SudokuBuilder.cpp

SudokuSolver.o: SudokuSolver.cpp
	$(COMPILER) $(FLAGS) -c SudokuSolver.cpp

.PHONY:clean run vrun

run: all
	./Proj Puzzles/Sudoku003.jpg
vrun: all
	valgrind --track-origins=yes ./Proj Puzzles/Sudoku003.jpg
clean:
	rm -f *.o $(EXECUTABLE) *~
