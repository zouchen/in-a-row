CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -MMD
OBJECTS=in-a-row.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=in-a-row

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm *.o in-a-row
.PHONY: clean
