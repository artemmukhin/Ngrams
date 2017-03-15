#pragma once

#include <pthread.h>

#include "../HashTable.h"

class ChangeThread
{
private:
    pthread_t thread;
    pthread_mutex_t mutex;
    pthread_cond_t wait;

    pthread_mutex_t *poolMutex;
    pthread_cond_t *poolCond;

    static void *routine(void *data);

    HashTable *tree;

public:
    int numberOfChangeTread;
    volatile bool isEmpty;
    bool isAdd;
    const char *str;
    uint64_t length;
    uint64_t num;

    ChangeThread();
    //ChangeThread(HashTable *tree);
    void setTree(HashTable *tree);
    void setMutexAndCond(pthread_mutex_t *mutex, pthread_cond_t *finished, int n);
    void signal();
};
