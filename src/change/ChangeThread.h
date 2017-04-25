#pragma once

#include <pthread.h>

#include "../HashTable.h"

class ChangePool;

class ChangeThread
{
private:
    pthread_t thread;
    pthread_mutex_t mutex;
    pthread_cond_t readyCond;
    bool actionIsReady;

    static void *threadFunction(void *data);

    HashTable *tree;
    ChangePool *pool;

    int ID;
    bool isAdd;
    const char *str;
    uint64_t length;
    uint64_t num;

public:
    ChangeThread();
    void init(ChangePool *pool, HashTable *tree, uint16_t id);
    void start();
    void routine();
    void setAction(bool isAdd, const char *str, uint64_t length, uint64_t num);
    //void signal();
};
