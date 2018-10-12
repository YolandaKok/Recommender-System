IOutils.o: IOutils.cpp
	g++ -std=c++11 -c IOutils.cpp
Hashutils.o: Hashutils.cpp
	g++ -std=c++11 -c Hashutils.cpp
Point.o: Point.cpp
	g++ -std=c++11 -c Point.cpp
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
ExactKnn.o: ExactKnn.cpp
	g++ -std=c++11 -c ExactKnn.cpp
all: main.o IOutils.o Point.o Hashutils.o ExactKnn.o
	g++ -std=c++11 -o lsh main.o IOutils.o Point.o Hashutils.o ExactKnn.o
clean:
	rm -f *.o lsh
