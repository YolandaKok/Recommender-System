IOutils.o: IOutils.cpp
	g++ -c IOutils.cpp
main.o: main.cpp
	g++ -c main.cpp
all: main.o IOutils.o
	g++ -o lsh main.o IOutils.o
clean:
	rm -f *.o lsh		
