#include "Solver.h"

Solver::Solver()
    : processor(&ngrams), change(&ngrams)
{}

void Solver::add(const char *str, uint64_t length, uint64_t num)
{
    change.add(str, length, num);
}

void Solver::remove(const char *str, uint64_t length, uint64_t num)
{
    change.remove(str, length, num);
}

void Solver::solve(const char *str, uint64_t length, uint64_t num)
{
    texts.push(str, length, num);
}

void Solver::flush()
{
    change.wait();

    //cout << "Solver: start processing queries" << endl;
    while (!texts.isEmpty()) {
        QueueNode *data = texts.pop();
        processor.process(data->str, data->length, data->num);
    }

    //ngrams.clear();// TODO clear commented
    std::fflush(stdout);
}

void Solver::waitForInit()
{
    change.wait();
}
