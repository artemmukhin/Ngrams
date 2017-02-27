//
// Created by opot on 27.02.17.
//

#ifndef NGRAMS_DATAPIPE_H
#define NGRAMS_DATAPIPE_H

#include <queue>
#include <string>

struct Query{
    int type; // -1 remove; 0 - query; 1 - add
    std::string str;
};

class DataPipe {

    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_state;

    std::queue<Query> *wait, *current;

public:

    DataPipe();

    Query next();

    void add(std::string &str);
    void remove(std::string &str);
    void process(std::string &text);

};


#endif //NGRAMS_DATAPIPE_H
