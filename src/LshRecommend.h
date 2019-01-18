#ifndef LSH_LSHRECOMMEND_H
#define LSH_LSHRECOMMEND_H
#include "Lsh.h"
#include <vector>
#include "Point.h"
#include <string>

using namespace std;

class LshRecommend {
    private:
        LSH *lsh;
        vector<Point*> user_points;
        vector<tuple<string, vector<string>>> coins_per_user;
        int P;
        double total_time;
    public:
        // Constructor
        LshRecommend(int L, int size, int k, vector<Point*> points, string lsh_family, int input_size, double dimension,
                double w, int P);
        LshRecommend(int L, int size, int k, vector<Point *> points, string lsh_family, int input_size,
                               double dimension, double w, int P, vector<Point *> queries);
        // Recommend k items
        vector<tuple<string, vector<string>>> getRecommendations(vector<string>& coin_names, int num_of_coins);
        void print(string outputFile, string exercise, ofstream& myfile);
        // Destructor
        ~LshRecommend();

};

#endif //LSH_LSHRECOMMEND_H
