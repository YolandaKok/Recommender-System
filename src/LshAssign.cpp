//
// Created by yolanda on 13/11/2018.
//

#include "LshAssign.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

LshAssign::LshAssign(LSH *lsh, Hypercube *cube, string metric): Assignment(metric) {
    /* Pointer to the Lsh Structure */
    this->lsh = lsh;
    this->cube = cube;
}


void LshAssign::assignCentroids(vector<Point*>& dataset, vector<Point*> centroids) {

    vector<int> arr;
    for(int i = 0; i < centroids.size(); i++) {
        arr.push_back(i);
    }

    int r = 2;
    int n = arr.size();
    //printCombination(arr, n, r);
    vector<int> data;
    data.resize(r);
    vector<pair<int,int>> results;
    // Print all combination using temprary array 'data[]'
    /* Find the combinations for the k centers */
    combinationUtil(arr, n, r, 0, data, 0, results);
    vector<double> distances;
    /* Find the minimum distance for the centers */
    /* Calculate the distance for every centroid */
    for(int i = 0; i < results.size(); i++) {
        /* Calculate Distance */
        if(!this->metric.compare("euclidean")) {
            distances.push_back(centroids.at(results.at(i).first)->euclidean(centroids.at(results.at(i).second)));
        }
        else if(!this->metric.compare("cosine")) {
            distances.push_back(centroids.at(results.at(i).first)->cosine(centroids.at(results.at(i).second)));
        }

    }
    /* Calculate the R initial value */
    double min = minimum(distances);
    double currentR = min / 2;

    int index_min;
    while(currentR == 0.0) {
        index_min = minimum_index(distances);
        distances.erase (distances.begin()+index_min);
        min = minimum(distances);
        currentR = min / 2;
        //cout << currentR << endl;
    }

    ofstream myfile;
    vector<double> distances_new;

    cout << currentR << "Current R" << endl;

    vector<Point*> currentPoints;
    vector<double> distances2;
    distances2.resize(centroids.size());
    vector<int> *clusters;
    vector<int>::iterator it;
    int newAssign = 0, countAssign = 0;
    int i = 0;
    /* Start of the Loop for range search */
    do {
        i++;
        //cout << "LOOP " << i << endl;
        int num_points = 0;
        newAssign = 0;
        for(int j = 0; j < centroids.size(); j++) {
            /* Return a vector of Point* */
            if(this->cube == NULL) {
                currentPoints = this->lsh->rangeSearch(centroids.at(j), currentR, myfile);
            }
            else {
                currentPoints = this->cube->rangeSearch(this->cube->findNearest(centroids.at(j)), centroids.at(j), currentR);
            }
            for( int z = 0; z < currentPoints.size(); z++ ) {
                // if it exists in assignedPoints
                // Keep assigned points in another array
                if(currentPoints.at(z)->getR() == 0.0 && currentPoints.at(z)->isCentroid() == 0) {
                    currentPoints.at(z)->setR(currentR);
                    currentPoints.at(z)->setClusters(j);
                    currentPoints.at(z)->setCluster(j);
                    newAssign++;
                }
                if((currentPoints.at(z)->getR() == currentR) && (currentPoints.at(z)->isCentroid() == 0)) {
                    it = find (currentPoints.at(z)->getClusters()->begin(), currentPoints.at(z)->getClusters()->end(), j);
                    if (it != currentPoints.at(z)->getClusters()->end() && currentPoints.at(z)->getClusters()->size() == 1) {

                    }
                    else {
                        currentPoints.at(z)->setClusters(j);
                        for(int w = 0; w < currentPoints.at(z)->getClusters()->size(); w++) {
                            if(!this->metric.compare("euclidean")) {
                                distances_new.push_back(currentPoints.at(z)->euclidean(centroids.at(currentPoints.at(z)->getClusters()->at(w))));
                            }
                            else if(!this->metric.compare("cosine")) {
                                distances_new.push_back(currentPoints.at(z)->cosine(centroids.at(currentPoints.at(z)->getClusters()->at(w))));
                            }
                        }
                        currentPoints.at(z)->setCluster(minimum_index(distances_new));
                        distances_new.clear();
                        newAssign++;
                    }
                }
            }
            currentPoints.clear();
        }

        if(newAssign < 5) {
            countAssign++;
        }
        currentR *= 2;
    } while(countAssign < 4);

    int count = 0, min_index;
    vector<double> remaining_distances;
    for( int i = 0; i < dataset.size(); i++ ) {
        if( dataset.at(i)->getR() == 0.0 && dataset.at(i)->isCentroid() == 0) {
            count++;
            /* Find the nearest centroid and assign it */
            for( int j = 0; j < centroids.size(); j++ ) {
                if(!metric.compare("euclidean")) {
                    remaining_distances.push_back(centroids.at(j)->euclidean(dataset.at(i)));
                }
                else if(!metric.compare("cosine")) {
                    remaining_distances.push_back(centroids.at(j)->cosine(dataset.at(i)));
                }
            }

            min_index = minimum_index(remaining_distances);
            dataset.at(i)->setCluster(min_index);
            remaining_distances.clear();
        }
        dataset.at(i)->setR(0.0);
        dataset.at(i)->getClusters()->clear();
    }
    cout << "Unassigned " << count << endl;
}

double LshAssign::minimum(vector<double> elements) {
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i))
            min = elements.at(i);
    }
    return min;
}


int LshAssign::minimum_index(vector<double> elements) {
    int index = 0;
    double min = elements.at(0);
    int i;
    for( i = 1; i < elements.size(); i++ ) {
        if(min > elements.at(i)) {
            min = elements.at(i);
            index = i;
        }
    }
    return index;
}


/* arr[] ---> Input Array
n	 ---> Size of input array
r	 ---> Size of a combination to be printed
index ---> Current index in data[]
data[] ---> Temporary array to store current combination
i	 ---> index of current element in arr[]	 */
void LshAssign::combinationUtil(vector<int> arr, int n, int r, int index, vector<int> data, int i, vector<pair<int,int>>& results)
{
    pair <int, int> values ;
    // Current cobination is ready, print it
    if (index == r)
    {
        values.first = data.at(0);
        values.second = data.at(1);
        results.push_back(values);
        return;
    }

    // When no more elements are there to put in data[]
    if (i >= n)
        return;

    // current is included, put next at next location
    data.at(index) = arr.at(i);
    combinationUtil(arr, n, r, index+1, data, i+1, results);

    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
    combinationUtil(arr, n, r, index, data, i+1, results);
}

