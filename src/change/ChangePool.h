#pragma once

#define CHANGE_THREAD_NUM 1

#include "ChangeThread.h"

class ChangePool
{
private:
    ChangeThread threads[CHANGE_THREAD_NUM];

public:
    ChangePool(HashTable *tree);
    void add(const char *str, int length, int num);
    void remove(const char *str, int length, int num);
    void wait();
};