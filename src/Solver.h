#pragma once

#include "HashTable.h"
#include "Queue.h"
#include "change/ChangePool.h"
#include "process/TextProcessor.h"

class Solver
{
private:
    HashTable ngrams;

    Queue texts;

    ChangePool change;
    TextProcessor processor;

public:
    Solver();
    void add(const char *str, uint64_t length, uint64_t num);
    void remove(const char *str, uint64_t length, uint64_t num);
    void solve(const char *str, uint64_t length, uint64_t num);
    void flush();
    void waitForInit();
};