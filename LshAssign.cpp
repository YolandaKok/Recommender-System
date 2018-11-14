//
// Created by yolanda on 13/11/2018.
//

#include "LshAssign.h"

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
        distances.push_back(centroids.at(results.at(i).first)->euclidean(centroids.at(results.at(i).second)));
    }
    /* Calculate the R initial value */
    double min = minimum(distances);
    double currentR = min / 2;
    /* Start of the Loop for range search */

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

