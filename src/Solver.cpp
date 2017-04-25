#include "Solver.h"

Solver::Solver()
    : processor(&ngrams), changePool(&ngrams)
//    : changePool(&ngrams)
{}

void Solver::add(const char *str, uint64_t length, uint64_t num)
{
    changePool.add(str, length, num);
}

void Solver::remove(const char *str, uint64_t length, uint64_t num)
{
    changePool.remove(str, length, num);
}

void Solver::solve(const char *str, uint64_t length, uint64_t num)
{
    texts.push(str, length, num);
}

void Solver::flush()
{
    changePool.waitAllThreads();

    while (!texts.isEmpty()) {
        QueueNode *data = texts.pop();
        processor.process(data->str, data->length, data->num);
    }

    std::fflush(stdout);
}

void Solver::waitForInit()
{
    changePool.waitAllThreads();
}
