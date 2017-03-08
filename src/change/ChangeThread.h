//
// Created by opot on 07.03.17.
//

#ifndef NGRAMS_CHNAGETHREAD_H
#define NGRAMS_CHNAGETHREAD_H

#include <pthread.h>

#include "../HashTable.h"

class ChangeThread {

    pthread_t thread;
    pthread_mutex_t mutex;
    pthread_cond_t wait;

    static void *routine(void *data);

    HashTable *tree;

public :
    volatile bool isEmpty;
    bool isAdd;
    const char* str;
    int length;
    int num;

    ChangeThread();
    ChangeThread(HashTable *tree);
    void signal();
};


#endif //NGRAMS_CHNAGETHREAD_H
