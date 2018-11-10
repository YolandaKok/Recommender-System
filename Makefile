IOutils.o: IOutils.cpp
	g++ -std=c++11 -c IOutils.cpp
Point.o: Point.cpp
	g++ -std=c++11 -c Point.cpp
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
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
Clustering.o: Clustering.cpp
	g++ -std=c++11 -c Clustering.cpp
Initialization.o: Initialization.cpp
	g++ -std=c++11 -c Initialization.cpp
RandomInit.o: RandomInit.cpp
	g++ -std=c++11 -c RandomInit.cpp
KmeansppInit.o: KmeansppInit.cpp
	g++ -std=c++11 -c KmeansppInit.cpp
Assignment.o: Assignment.cpp
	g++ -std=c++11 -c Assignment.cpp
Update.o: Update.cpp
	g++ -std=c++11 -c Update.cpp
mainCluster.o: mainCluster.cpp
	g++ -std=c++11 -c mainCluster.cpp
lsh: main.o IOutils.o Point.o H.o F.o Hashtable.o Lsh.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
	g++ -std=c++11 -o lsh main.o IOutils.o Point.o H.o F.o Hashtable.o Lsh.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
cube: main2.o Hypercube.o IOutils.o Point.o H.o F.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
	g++ -std=c++11 -o cube main2.o Hypercube.o IOutils.o Point.o H.o F.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
cluster: mainCluster.o Point.o IOutils.o Clustering.o Initialization.o RandomInit.o KmeansppInit.o Update.o Assignment.o
	g++ -std=c++11 -o cluster mainCluster.o Point.o IOutils.o Clustering.o Initialization.o RandomInit.o KmeansppInit.o Update.o Assignment.o
clean:
	rm -f *.o lsh cube cluster
