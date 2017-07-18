CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
all: p3-1 p3-2 p3-3 p3-4 p3-5 p3-6 p3-7

p3-1: Proj03-1.cpp
	g++ -std=c++11 -g Proj03-1.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-1

p3-2: Proj03-2.cpp
	g++ -std=c++11 -g Proj03-2.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-2

p3-3: Proj03-3.cpp
	g++ -std=c++11 -g Proj03-3.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-3

p3-4: Proj03-4.cpp
	g++ -std=c++11 -g Proj03-4.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-4

p3-5: Proj03-5.cpp
	g++ -std=c++11 -g Proj03-5.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-5

#test: test.cpp
#	g++ -std=c++11 -g test.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o test

p3-6: Proj03-6.cpp
	g++ -std=c++11 -g Proj03-6.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-6

p3-7: Proj03-7.cpp
	g++ -std=c++11 -g Proj03-7.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-7

.PHONY:clean

clean:
	rm p3-1 p3-2 p3-3 p3-4 p3-5 p3-6 p3-7
