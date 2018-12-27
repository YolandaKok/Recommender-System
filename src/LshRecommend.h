#ifndef LSH_LSHRECOMMEND_H
#define LSH_LSHRECOMMEND_H
#include "Lsh.h"
#include <vector>
#include "Point.h"

using namespace std;

class LshRecommend {
    private:
        LSH *lsh;
        vector<Point*> user_points;
        int P;
    public:
        // Constructor
        LshRecommend(int L, int size, int k, vector<Point*> points, string lsh_family, int input_size, double dimension, double w, int P);
        // Recommend k items
        void getRecommendations();
        // Destructor
        ~LshRecommend();

};

#endif //LSH_LSHRECOMMEND_H
