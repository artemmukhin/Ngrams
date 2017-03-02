//
// Created by opot on 27.02.17.
//

#ifndef NGRAMS_DATAPIPE_H
#define NGRAMS_DATAPIPE_H

#include <queue>
#include <string>

struct Query{
    int type; // -1 remove; 0 - query; 1 - add
    int length;
    const char *str;
};

class DataPipe {

    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_state;

    std::queue<Query> *wait, *current;

public:

    DataPipe();

    Query next();

    void add(const char *str, int length);
    void remove(const char *str, int length);
    void process(const char *str, int length);

};


#endif //NGRAMS_DATAPIPE_H
