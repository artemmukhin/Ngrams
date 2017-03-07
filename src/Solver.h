#pragma once

#include "ProcessingThread.h"

class Solver
{
    ProcessingThread thread[THREAD_NUM];
    uint64_t waitOut;
    uint64_t total;

public:
    Solver();
    void add(const char *str, uint64_t length);
    void remove(const char *str, uint64_t length);
    void process(const char *text, uint64_t length, uint64_t num);

    void flush();
    void wait();
};
