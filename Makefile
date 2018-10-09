IOutils.o: IOutils.cpp
	g++ -c IOutils.cpp
Point.o: Point.cpp
	g++ -c Point.cpp
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
all: main.o IOutils.o Point.o
	g++ -std=c++11 -o lsh main.o IOutils.o Point.o
clean:
	rm -f *.o lsh
