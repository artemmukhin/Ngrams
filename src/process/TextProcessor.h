#pragma once


#include <pthread.h>

#include "../HashTable.h"
#include "../Constants.h"

struct ThreadData
{
    const char *str;
    uint64_t start;
    uint64_t end;
    uint64_t length;
    uint64_t num;

    pthread_mutex_t mutex;

    HashTable *tree;
    FoundSet *result;

    uint64_t **hashes;
};

class TextProcessor
{
private:
    pthread_t threads[PROCESS_THREAD_NUM];
    ThreadData data[PROCESS_THREAD_NUM];
    uint64_t *hashes;

    pthread_cond_t startCond;

    static void *routine(void *data);

public:
    TextProcessor() = delete;
    TextProcessor(HashTable *tree);
    void process(const char *str, uint64_t length, uint64_t num);
};
