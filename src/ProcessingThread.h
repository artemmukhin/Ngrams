//
// Created by opot on 26.02.17.
//

#ifndef NGRAMS_PROCESSINGTHREAD_H
#define NGRAMS_PROCESSINGTHREAD_H

#include <pthread.h>
#include <queue>

#include "HashTable.h"
#include "DataPipe.h"
#include "ResultPipe.h"

class ProcessingThread {

    HashTable ngrams;

    pthread_t thread;

    static void* routine(void* data);

public:

    DataPipe pipe;
    ResultPipe result;

    ProcessingThread();

    friend class Solver;

};


#endif //NGRAMS_PROCESSINGTHREAD_H
