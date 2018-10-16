IOutils.o: IOutils.cpp
	g++ -std=c++11 -c IOutils.cpp
Point.o: Point.cpp
	g++ -std=c++11 -c Point.cpp
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
ExactKnn.o: ExactKnn.cpp
	g++ -std=c++11 -c ExactKnn.cpp
H.o: H.cpp
	g++ -std=c++11 -c H.cpp
F.o: F.cpp
	g++ -std=c++11 -c F.cpp
Lsh.o: Lsh.cpp
	g++ -std=c++11 -c Lsh.cpp
Hashtable.o: Hashtable.cpp
	g++ -std=c++11 -c Hashtable.cpp
all: main.o IOutils.o Point.o ExactKnn.o H.o F.o Hashtable.o Lsh.o
	g++ -std=c++11 -o lsh main.o IOutils.o Point.o ExactKnn.o H.o F.o Hashtable.o Lsh.o
clean:
	rm -f *.o lsh
