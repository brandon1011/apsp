TARGET=apsp
CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -w
SRC=Graph.cpp Vertex.cpp FloydWarshall.cpp Kruskall.cpp UnionFind.cpp Dijkstra.cpp TestBench.cpp main.cpp
TRASH=${TARGET}

all:
	${CC} ${CFLAGS} ${SRC} -o ${TARGET}
clean:
	rm ${TARGET}
