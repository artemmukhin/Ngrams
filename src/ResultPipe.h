//
// Created by opot on 02.03.17.
//

#ifndef NGRAMS_RESULTPIPE_H
#define NGRAMS_RESULTPIPE_H

#include <string>
#include <queue>

struct Result{
    std::string* result;
    int num;
};

enum ThreadState{
    FREE, HOLD
};

class ResultPipe {

std::queue<Result> pipe;

public:
    ThreadState state;

    ResultPipe();
    void Push(std::string* result);
    bool isReady(int num);
    bool TryOut(int curr_num);
};


#endif //NGRAMS_RESULTPIPE_H
