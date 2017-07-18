CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
COMPILER = g++
FLAGS = -g -std=c++11
EXECUTABLE = Proj

all: Driver.o SudokuBuilder.o SudokuSolver.o
	$(COMPILER) $(FLAGS) ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o $(EXECUTABLE) Driver.o SudokuBuilder.o SudokuSolver.o

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

SudokuBuilder.o: SudokuBuilder.cpp
	$(COMPILER) $(FLAGS) -c SudokuBuilder.cpp

SudokuSolver.o: SudokuSolver.cpp
	$(COMPILER) $(FLAGS) -c SudokuSolver.cpp

.PHONY:clean

clean:
	rm -f *.o $(EXECUTABLE)
