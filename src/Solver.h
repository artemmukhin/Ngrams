//
// Created by opot on 07.03.17.
//

#ifndef NGRAMS_SOLVER_H
#define NGRAMS_SOLVER_H


#include "HashTable.h"
#include "Queue.h"
#include "change/ChangePool.h"
#include "process/TextProcessor.h"

class Solver {

    HashTable ngrams;

    Queue texts;

    ChangePool change;
    TextProcessor processor;

public:
    Solver();
    void add(const char* str, int length, int num);
    void remove(const char* str, int length, int num);
    void solve(const char* str, int length, int num);
    void flush();
};


#endif //NGRAMS_SOLVER_H
