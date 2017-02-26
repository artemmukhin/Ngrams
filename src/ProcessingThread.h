//
// Created by opot on 26.02.17.
//

#ifndef NGRAMS_PROCESSINGTHREAD_H
#define NGRAMS_PROCESSINGTHREAD_H

#include <pthread.h>
#include <queue>

#include "HashTable.h"

struct Query{
    int type; // -1 remove; 0 - query; 1 - add
    string str;
};

enum ThreadState{
    FREE, OUT, HOLD
};

class ProcessingThread {

    HashTable ngrams;
    queue<Query> query;

    pthread_t thread;
    ThreadState state;
    volatile bool isEmpty;

    string result;
    int num;

    static void* routine(void* data);

public:

    pthread_mutex_t queue_state;
    ProcessingThread();

    void add(string &str);
    void remove(string &str);
    void process(string &text, int num);

    ThreadState getState();
    int getNum();
    void printResult();

    friend class Solver;

};


#endif //NGRAMS_PROCESSINGTHREAD_H
