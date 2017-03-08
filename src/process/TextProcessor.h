//
// Created by opot on 07.03.17.
//

#ifndef NGRAMS_TEXTPROCESSOR_H
#define NGRAMS_TEXTPROCESSOR_H

#define PROCESS_THREAD_NUM 20

#include <pthread.h>

#include "../HashTable.h"

struct ThreadData{
    const char * str;
    int full_length;
    int part_length;
    int num;

    pthread_mutex_t mutex;
    pthread_cond_t *start;

    HashTable* tree;
};

class TextProcessor {

    pthread_t threads[PROCESS_THREAD_NUM];
    ThreadData data[PROCESS_THREAD_NUM];

    pthread_cond_t start;

    static void* routine(void* data);

public:
    TextProcessor(HashTable *tree);
    void process(const char* str, int length, int num);
};


#endif //NGRAMS_TEXTPROCESSOR_H
