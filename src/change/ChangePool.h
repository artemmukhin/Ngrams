#pragma once

#include "ChangeThread.h"
#include "../Constants.h"

class ChangePool
{
private:
    pthread_mutex_t mutex;
    pthread_cond_t finished[CHANGE_THREAD_NUM];

    ChangeThread threads[CHANGE_THREAD_NUM];

public:
    ChangePool(HashTable *tree);
    void add(const char *str, int length, int num);
    void remove(const char *str, int length, int num);
    void wait();
};