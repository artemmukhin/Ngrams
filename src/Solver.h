//
// Created by opot on 26.02.17.
//

#ifndef NGRAMS_SOLVER_H
#define NGRAMS_SOLVER_H

#include "ProcessingThread.h"

#define THREAD_NUM 4

class Solver {

    ProcessingThread thread[THREAD_NUM];
    int waitOut;

public:
    Solver();
    void add(string &str);
    void remove(string &str);
    void process(string &text, int num);

    void wait();
};


#endif //NGRAMS_SOLVER_H
