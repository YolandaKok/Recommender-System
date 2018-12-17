#define LINE_SIZE 500
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include "IOutils.h"
#include "Point.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "H.h"
#include <sstream>
#include "F.h"
#include <string>
#include <map>
#include "Tweet.h"
#include "Point.h"
#include <unordered_map>

using namespace std;
/* Read the dataset file */
vector<Point*> readInput(const char filename[], const char seperator[], const char delimiter[], int k, int& size, int input, double& R, char metric[10]) {
  /* Initialize random seed */
  FILE *fp = NULL;
  char line[LINE_SIZE];
  char *name = NULL, *token = NULL, *delimiters = NULL;
  char *ptr = NULL;
  /* Array of points */
  vector<Point*> points;
  delimiters = (char*)malloc(strlen(seperator) + strlen(delimiter) + 1);
  strcat(delimiters, seperator);
  strcat(delimiters, delimiter);
  //name = (char*)malloc(strlen(filename) + strlen("") + 1);
  //sprintf(name, "%s", filename);
  /* Open the file */
  fp = fopen(filename,"r");
  if(fp == NULL)
    assert(fp != NULL);

  /* Set the id for the point */
  int i = 0;
  int flag = 0;
  /* Read line by line */
  while (fgets(line, LINE_SIZE, fp)) {
    token = strtok(line, delimiters);
    if(!strcmp(token, "Radius:")) {
      token = strtok(NULL, delimiters);
      R = atof(token);
      flag = 1;
    }
    if(!strcmp(token, "@metric")) {
      token = strtok(NULL, delimiters);
      strcpy(metric, token);
      cout << metric << endl;
      //metric = token;
      flag = 1;
    }
    if(flag == 0) {
    /* Create a Point */
    Point *point = new Point();
    //point->setId(i);
    int k = 0;
    while( token != NULL ) {
      if(k == 0) {
        point->setId(token);
        k++;
      }
      else {
        /* Make token a double */
        point->addCoord(atof(token));
      }
      /* Make token a double */
      /* Create an array of points */
      //point->addCoord(atof(token));
      token = strtok(NULL, delimiters);
   }
   //point->print();
   i++;
   points.push_back(point);}
   flag = 0;
  }

  if(input)
    size = points.size();

  free(delimiters);
  free(name);
  return points;
}


/* New I/O read using C++ */
vector<Point*> readFile(const char filename[], int k, int& size, int input, double& R, string& metric, char separator) {
  string line;
  string word;
  vector<Point*> points;
  ifstream myfile (filename);
  int flag = 0;
  int count = 0, countPoint = 0;
  Point *point;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      /* Find the metric */
      //cout << line << endl;
      istringstream iss(line);
      while(getline(iss, word, separator)) {
       /* do stuff with word */
       /* If it is input small find metric */
          if(!word.compare("@metric")) {
             iss >> word;
             metric = word;
           }
          else if(!word.compare("Radius:")) {
             iss >> word;
             R = stod(word);
          }
          else {
            flag = 1;
            if(countPoint == 0) {
              point = new Point();
              //cout << word << endl;
              point->setId(word);
              countPoint++;
            }
            else {
              point->addCoord(stod(word));
            }
          }
      }
      if(flag) {
        points.push_back(point);
      }
      count++;
      countPoint = 0;
    }
    myfile.close();
  }
  if(input)
    size = points.size();
  return points;
}

/* New I/O read using C++ */
map<string, vector<Tweet*>> readFileRecommend(const char filename[], int& size, int input, int& P, char separator) {
  string line;
  string word;
  Tweet *tweet;
  //vector<Tweet*> points;
  map<string, vector<Tweet*>> points;
  ifstream myfile (filename);
  int flag = 0;
  int count = 0, countPoint = 0;
  string userId;
  Point *point;
  if (myfile.is_open())
  {
    while ( getline (myfile,line, '\n') )
    {
      /* Find the metric */
      //cout << line << endl;
      istringstream iss(line);
      while(getline(iss, word, separator)) {
        /* do stuff with word */
        /* If it is input small find metric */
        if(word.compare("P:") == 0) {
          iss >> word;
          P = stoi(word);
        }
        else {
          flag = 1;
          if(countPoint == 0) {
            //cout << word << endl;
              if(count < 10) {
                  //cout << word << endl;
              }
            userId = word;
            countPoint++;
          }
          else if(countPoint == 1) {
            tweet = new Tweet(word);
            countPoint++;
          }
          else {
              tweet->addWord(word);
          }
        }
      }
      if(flag) {

        //cout << userId << endl;

        points[userId].push_back(tweet);
      }
      count++;
      countPoint = 0;
    }
    myfile.close();
  }
  /*if(input)
    size = points.size();*/
  return points;
}

void readDictionary(const char filename[], unordered_map<string, double>* dictionary, char separator) {
  string line;
  string word;
  ifstream myfile (filename);
  int flag = 0;
  int count = 0, countPoint = 0;
  string key;
  if (myfile.is_open())
  {
    while ( getline (myfile,line, '\n') )
    {
      /* Find the metric */
      //cout << line << endl;
      istringstream iss(line);
      while(getline(iss, word, separator)) {
        /* do stuff with word */
        /* If it is input small find metric */
          if(countPoint == 0) {
            //cout << word << endl;
            key = word;
            countPoint++;
          }
          else if(countPoint == 1) {
            dictionary->insert ( pair<string,double>(key,stod(word)) );
            countPoint++;
          }
      }
      countPoint = 0;
    }
    myfile.close();
  }
}

/* Read the arguments */
int readArgs(char* argv[], int argc, char*& input_file, char*& queryFile, int& k, int& L, char*& outputFile, int& probes, int& M) {
  int i;
  if(!strcmp(argv[0], "./cube") || !strcmp(argv[0], "./lsh")) {
      //printf("lsh \n");
      /* Read the arguments for the lsh */
      /* Code to handle the command line flags */
      for(i = 1; i < argc; i += 2) {
        if(!strcmp(argv[i], "-d")) {
          input_file = (char*)malloc(strlen(argv[i+1]) + 1);
          strcpy(input_file, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-q")) {
          queryFile = (char*)malloc(strlen(argv[i+1]) + 1);
          strcpy(queryFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-k")) {
          k = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-L")) {
          L = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-o")) {
          outputFile = (char*)malloc(strlen(argv[i+1]) + 1);
          strcpy(outputFile, argv[i+1]);
        }
        else if(!strcmp(argv[i], "-probes")) {
          probes = atoi(argv[i+1]);
        }
        else if(!strcmp(argv[i], "-M")) {
          M = atoi(argv[i+1]);
        }
      }
  }
}

/* Read the configuration file */
int readConf(const char filename[], int& k, int& L, int& clusters, int& probes, double& w) {
  string line;
  string word;
  ifstream myfile (filename);

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      cout << line << endl;
      istringstream iss(line);
      while (iss >> word) {
        /* do stuff with word */
        /* If it is input small find metric */
        if (!word.compare("number_of_hash_functions:")) {
            iss >> word;
            k = stoi(word);
        }
        else if (!word.compare("number_of_hash_tables:")) {
            iss >> word;
            L = stoi(word);
        }
        else if (!word.compare("number_of_clusters:")) {
            iss >> word;
            clusters = stoi(word);
        }
        else if(!word.compare("number_of_probes:")) {
            iss >> word;
            probes = stoi(word);
        }
        else if(!word.compare("w_parameter:")) {
            iss >> word;
            w = stod(word);
        }
      }
    }
    myfile.close();
  }
  return 1;
}
