//
// Created by opot on 21.02.17.
//

#ifndef NGRAMS_SOLVER_H
#define NGRAMS_SOLVER_H

#include <vector>
#include <string>

#include "NgramTree.h"


#define NUM_THREADS 2

class Solver {

    struct Changes{
        string ngram;
        int action; // -1 - deletion, 1 - addition
        int num;
    };

    struct ThreadData {
        string * text;
        int num;
        int thread_num;
        Solver* solver;

        ThreadData(string* text, int num, int thread_num, Solver* solver){
            this->text = text;
            this->num = num;
            this->thread_num = thread_num;
            this->solver = solver;
        }

    };

    NgramTree ngrams;
    vector<Changes> changes;

    string result[NUM_THREADS];

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

public:
    Solver();

    void add(string& ngram, int num);
    void remove(string& ngram, int num);
    void rebuild();
    static void* compute(void* data);

    void solve(string* texts, int* nums, int count);

};


#endif //NGRAMS_SOLVER_H
