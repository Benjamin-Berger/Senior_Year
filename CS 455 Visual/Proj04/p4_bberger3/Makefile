CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
all: p4-1 p4-2 p4-3 p4-4

p4-1: Proj04-1.cpp
	g++ -std=c++11 -g Proj04-1.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p4-1

p4-2: Proj04-2.cpp
	g++ -std=c++11 -g Proj04-2.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p4-2

p4-3: Proj04-3.cpp
	g++ -std=c++11 -g Proj04-3.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p4-3

p4-4: Proj04-4.cpp
	g++ -std=c++11 -g Proj04-4.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p4-4

#p3-5: Proj03-5.cpp
#	g++ -std=c++11 -g Proj03-5.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-5

#test: test.cpp
#	g++ -std=c++11 -g test.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o test

#p3-6: Proj03-6.cpp
#	g++ -std=c++11 -g Proj03-6.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-6

#p3-7: Proj03-7.cpp
#	g++ -std=c++11 -g Proj03-7.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p3-7

.PHONY:clean

clean:
	rm p4-1 p4-2 p4-3 p4-4 p3-5 p3-6 p3-7
