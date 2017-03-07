#include "Solver.h"

#include <chrono>
#include <thread>

Solver::Solver()
{
    waitOut = 0;
    total = 0;
}

void Solver::add(const char *str, uint64_t length)
{
    for (int i = 0; i < THREAD_NUM; i++)
        thread[i].pipe.add(str, length);
}

void Solver::remove(const char *str, uint64_t length)
{
    for (int i = 0; i < THREAD_NUM; i++)
        thread[i].pipe.remove(str, length);
}

void Solver::flush()
{
    while (waitOut != total)
        for (int i = 0; i < THREAD_NUM; i++)
            waitOut += thread[i].result.TryOut(waitOut);
}

void Solver::wait()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_WAIT));
    /*for(int i = 0; count != THREAD_NUM; i++) {
        pthread_mutex_lock(&thread[i].queue_state);
        if(thread[i].query.empty()) count++;
        else i--;
        pthread_mutex_unlock(&thread[i].queue_state);
    }*/
}

void Solver::process(const char *str, uint64_t length, uint64_t num)
{
    int i = 0;
    total++;
    while (1) {
        waitOut += thread[i].result.TryOut(waitOut);

        if (thread[i].result.isReady(num)) {
            thread[i].pipe.process(str, length);
            break;
        }

        i = (i + 1) % THREAD_NUM;
    }
}