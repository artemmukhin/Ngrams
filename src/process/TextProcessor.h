#pragma once


#include <pthread.h>

#include "../HashTable.h"
#include "../Constants.h"

struct ThreadData
{
    const char *str;
    int start;
    int end;
    int length;
    int num;

    pthread_mutex_t mutex;
    pthread_cond_t *wake_up;
    bool isStarted;

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
    void process(const char *str, int length, int num);
};
