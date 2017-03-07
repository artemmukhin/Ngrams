//
// Created by opot on 07.03.17.
//

#ifndef NGRAMS_CHANGEPOOL_H
#define NGRAMS_CHANGEPOOL_H

#define CHANGE_THREAD_NUM 30

#include "ChangeThread.h"

class ChangePool {

ChangeThread threads[CHANGE_THREAD_NUM];

public :
    ChangePool(HashTable *tree);
    void add(const char* str, int length, int num);
    void remove(const char* str, int length, int num);
    void wait();
};


#endif //NGRAMS_CHANGEPOOL_H
