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
H_euclidean.o: H_euclidean.cpp
	g++ -std=c++11 -c H_euclidean.cpp
H_cosine.o: H_cosine.cpp
	g++ -std=c++11 -c H_cosine.cpp
F.o: F.cpp
	g++ -std=c++11 -c F.cpp
F_euclidean.o: F_euclidean.cpp
	g++ -std=c++11 -c F_euclidean.cpp
F_cosine.o: F_cosine.cpp
	g++ -std=c++11 -c F_cosine.cpp
Lsh.o: Lsh.cpp
	g++ -std=c++11 -c Lsh.cpp
read.o: read.cpp
	g++ -std=c++11 -c read.cpp
Hashtable.o: Hashtable.cpp
	g++ -std=c++11 -c Hashtable.cpp
Hypercube.o: Hypercube.cpp
	g++ -std=c++11 -c Hypercube.cpp
F_hypercube_euclidean.o: F_hypercube_euclidean.cpp
	g++ -std=c++11 -c F_hypercube_euclidean.cpp
F_hypercube_cosine.o: F_hypercube_cosine.cpp
	g++ -std=c++11 -c F_hypercube_cosine.cpp
main2.o: main2.cpp
	g++ -std=c++11 -c main2.cpp
lsh: main.o IOutils.o Point.o ExactKnn.o H.o F.o Hashtable.o Lsh.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o read.o
	g++ -std=c++11 -o lsh main.o IOutils.o Point.o ExactKnn.o H.o F.o Hashtable.o Lsh.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o read.o
cube: main2.o Hypercube.o IOutils.o Point.o H.o F.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o ExactKnn.o F_hypercube_cosine.o read.o
	g++ -std=c++11 -o cube main2.o Hypercube.o IOutils.o Point.o H.o F.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o ExactKnn.o F_hypercube_cosine.o read.o
clean:
	rm -f *.o lsh cube
