#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {

    bool validate = false;
    char *inputFile = NULL, *outputFile = NULL;
    srand(time(NULL));

    vector<string> coins = {"ethereum", "bitcoin", "stellar", "tether"};
    map<string, double> dictionary;
    dictionary["bad"] = -2.0;
    dictionary["good"] = 2.0;
    dictionary["profitable"] = 1.5;

    for(int i = 1; i < argc; i += 2) {
        /* Input File */
        if(!strcmp(argv[i], "-d")) {
            inputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(inputFile, argv[i+1]);
        }
            /* Configuration File */
        else if(!strcmp(argv[i], "-o")) {
            outputFile = (char*)malloc(strlen(argv[i+1]) + 1);
            strcpy(outputFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-validate")) {
            validate = true;
        }
    }

    // Read Input File


    return 1;
}
