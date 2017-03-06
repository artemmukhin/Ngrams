#pragma once

#include <string>
#include <queue>

struct Result
{
    std::string *result;
    uint64_t num;
};

enum ThreadState
{
    FREE, HOLD
};

class ResultPipe
{

    std::queue<Result> pipe;

public:
    ThreadState state;

    ResultPipe();

    void Push(std::string *result);

    bool isReady(uint64_t num);

    bool TryOut(uint64_t curr_num);
};
