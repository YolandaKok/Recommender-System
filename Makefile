SRC1 = src/
OBJS1 = main.o IOutils.o Point.o H.o F.o Hashtable.o Lsh.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
OBJS2 = main2.o Hypercube.o IOutils.o Point.o H.o F.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F_hypercube_euclidean.o F_hypercube_cosine.o
OBJS3 = mainCluster.o Point.o IOutils.o Clustering.o Initialization.o RandomInit.o KmeansppInit.o Update.o Assignment.o LloydsAssign.o KmeansUpdate.o LshAssign.o Lsh.o Hashtable.o F_euclidean.o H_euclidean.o F_cosine.o H_cosine.o F.o H.o F_hypercube_euclidean.o F_hypercube_cosine.o PAMUpdate.o Hypercube.o
OBJS4 = mainRecommend.o Tweet.o
LIBS = -pthread libgtest.a
INC = -I googletest/googletest \
			-I googletest/googletest/include \
			-I googlemock/googlemock \
			-I googlemock/googlemock/include \
			-I src \
			-I test

EXE1 = lsh
EXE2 = cube
EXE3 = cluster
EXE4 = recommendation

lsh: $(OBJS1)
	g++ -o $(EXE1) $(CFLAGS) $(OBJS1) $(LIBS)
cube: $(OBJS2)
	g++ -o $(EXE2) $(CFLAGS) $(OBJS2) $(LIBS)
cluster: $(OBJS3)
	g++ -o $(EXE3) $(CFLAGS) $(OBJS3) $(LIBS)
recommendation: $(OBJS4)
	g++ -o $(EXE4) $(CFLAGS) $(OBJS4) $(LIBS)

IOutils.o: src/IOutils.cpp
	g++ -c -o IOutils.o src/IOutils.cpp -std=c++14
Point.o: src/Point.cpp
	g++ -c -o Point.o src/Point.cpp -std=c++14
main.o: src/main.cpp
	g++ -c -o main.o src/main.cpp -std=c++14
H.o: src/H.cpp
	g++ -c -o H.o src/H.cpp -std=c++14
H_euclidean.o: src/H_euclidean.cpp
	g++ -c -o H_euclidean.o src/H_euclidean.cpp -std=c++14
H_cosine.o: src/H_cosine.cpp
	g++ -c -o H_cosine.o src/H_cosine.cpp -std=c++14
F.o: src/F.cpp
	g++ -c -o F.o src/F.cpp -std=c++14
F_euclidean.o: src/F_euclidean.cpp
	g++ -c -o F_euclidean.o src/F_euclidean.cpp -std=c++14
F_cosine.o: src/F_cosine.cpp
	g++ -c -o F_cosine.o src/F_cosine.cpp -std=c++14
Lsh.o: src/Lsh.cpp
	g++ -c -o Lsh.o src/Lsh.cpp -std=c++14
Hashtable.o: src/Hashtable.cpp
	g++ -c -o Hashtable.o src/Hashtable.cpp -std=c++14
Hypercube.o: src/Hypercube.cpp
	g++ -c -o Hypercube.o src/Hypercube.cpp -std=c++14
F_hypercube_euclidean.o: src/F_hypercube_euclidean.cpp
	g++ -c -o F_hypercube_euclidean.o src/F_hypercube_euclidean.cpp -std=c++14
F_hypercube_cosine.o: src/F_hypercube_cosine.cpp
	g++ -c -o F_hypercube_cosine.o src/F_hypercube_cosine.cpp -std=c++14
main2.o: src/main2.cpp
	g++ -c -o main2.o src/main2.cpp -std=c++14
Clustering.o: src/Clustering.cpp
	g++ -c -o Clustering.o src/Clustering.cpp -std=c++14
Initialization.o: src/Initialization.cpp
	g++ -c -o Initialization.o src/Initialization.cpp -std=c++14
RandomInit.o: src/RandomInit.cpp
	g++ -c -o RandomInit.o src/RandomInit.cpp -std=c++14
KmeansppInit.o: src/KmeansppInit.cpp
	g++ -c -o KmeansppInit.o src/KmeansppInit.cpp -std=c++14
Assignment.o: src/Assignment.cpp
	g++ -c -o Assignment.o src/Assignment.cpp -std=c++14
LloydsAssign.o: src/LloydsAssign.cpp
	g++ -c -o LloydsAssign.o src/LloydsAssign.cpp -std=c++14
LshAssign.o: src/LshAssign.cpp
	g++ -c -o LshAssign.o src/LshAssign.cpp -std=c++14
Update.o: src/Update.cpp
	g++ -c -o Update.o src/Update.cpp -std=c++14
KmeansUpdate.o: src/KmeansUpdate.cpp
	g++ -c -o KmeansUpdate.o src/KmeansUpdate.cpp -std=c++14
PAMUpdate.o: src/PAMUpdate.cpp
	g++ -c -o PAMUpdate.o src/PAMUpdate.cpp -std=c++14
mainCluster.o: src/mainCluster.cpp
	g++ -c -o mainCluster.o src/mainCluster.cpp -std=c++14
mainRecommend.o: src/mainRecommend.cpp
	g++ -c -o mainRecommend.o src/mainRecommend.cpp -std=c++14
Tweet.o: src/Tweet.cpp
	g++ -c -o Tweet.o src/Tweet.cpp -std=c++14
clean:
	rm -f *.o lsh cube cluster recommendation
