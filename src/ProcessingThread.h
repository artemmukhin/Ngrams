#pragma once

#include <pthread.h>
#include <queue>

#include "HashTable.h"
#include "DataPipe.h"
#include "ResultPipe.h"

class ProcessingThread
{

    HashTable ngrams;

    pthread_t thread;

    static void *routine(void *data);

public:

    DataPipe pipe;
    ResultPipe result;

    ProcessingThread();

    friend class Solver;

};