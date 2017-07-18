CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
all: p1-1 p1-3 p2 p3

p1-1: Proj01_Part1-1.cpp
	g++ -g Proj01_Part1-1.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p1-1

p1-3: Proj01_Part1-3.cpp
	g++ -g Proj01_Part1-3.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p1-3

p2: Proj01_Part2.cpp
	g++ -g Proj01_Part2.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p2

p3: Proj01_Part3.cpp
	g++ -g Proj01_Part3.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3


.PHONY:clean

clean:
	rm p1-1 p1-3 p2 p3