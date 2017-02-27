//
// Created by opot on 26.02.17.
//

#ifndef NGRAMS_PROCESSINGTHREAD_H
#define NGRAMS_PROCESSINGTHREAD_H

#include <pthread.h>
#include <queue>

#include "HashTable.h"
#include "DataPipe.h"

enum ThreadState{
    FREE, OUT, HOLD
};


class ProcessingThread {

    HashTable ngrams;

    pthread_t thread;

    ThreadState state;
    string result;
    int num;

    static void* routine(void* data);

public:

    DataPipe pipe;

    ProcessingThread();

    int getNum();
    void printResult();

    friend class Solver;

};


#endif //NGRAMS_PROCESSINGTHREAD_H
