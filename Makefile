CXX=g++-5
CXXFLAGS=-g -std=c++14 -Wall -MMD -Werror=vla  
EXEC=biquadris
OBJECTS=main.o Cell.o Grid.o Block.o SShape.o JShape.o OShape.o IShape.o LShape.o ZShape.o TShape.o level.o level_0.o Single.o level_1.o level_2.o level_3.o level_4.o window.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
