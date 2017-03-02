//
// Created by opot on 26.02.17.
//

#ifndef NGRAMS_SOLVER_H
#define NGRAMS_SOLVER_H

#include "ProcessingThread.h"

#define THREAD_NUM 40

class Solver {

    ProcessingThread thread[THREAD_NUM];
    int waitOut;
    int total;

public:
    Solver();
    void add(const char *str, int length);
    void remove(const char *str, int length);
    void process(const char *text, int length, int num);

    void flush();
    void wait();
};


#endif //NGRAMS_SOLVER_H
