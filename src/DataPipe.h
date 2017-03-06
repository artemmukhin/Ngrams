#pragma once
#include <queue>
#include <string>
#include "pthread.h"

struct Query
{
    int type; // -1 remove; 0 - query; 1 - add
    uint64_t length;
    const char *str;
};

class DataPipe
{
    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_state;

    std::queue<Query> *wait, *current;

public:

    DataPipe();

    Query next();

    void add(const char *str, uint64_t length);

    void remove(const char *str, uint64_t length);

    void process(const char *str, uint64_t length);
};
