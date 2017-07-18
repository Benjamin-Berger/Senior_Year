CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
all: proj

proj: Proj.cpp
	g++ -std=c++11 -g Proj.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o proj

#p2-2: Proj02-2.cpp
#	g++ -std=c++11 -g Proj02-2.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p2-2

#p2-3: Proj02-3.cpp
#	g++ -std=c++11 -g Proj02-3.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p2-3

#p2-4: Proj02-4.cpp
#	g++ -std=c++11 -g Proj02-4.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o p2-4

#test: test.cpp
#	g++ -std=c++11 -g test.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o test



.PHONY:clean

clean:
	rm proj
