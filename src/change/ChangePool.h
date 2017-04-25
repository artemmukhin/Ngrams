#pragma once

#include "ChangeThread.h"
#include "../Constants.h"

/*
 * Сделать нормальный тредпул, а именно:
 *  - в ChangePool::add/remove не делать "бесконечный цикл", а брать свободный тред со стека
 *  - в этот стек свободные треды будут приходить сами по завершении своей работы
 *  - - т.е. нужно агрегировать пул в каждый тред, чтобы тред вызывал что-то вроде pool.ready(this)
 */

// thread pool
class ChangePool
{
private:
    ChangeThread *threadStack[CHANGE_THREAD_NUM];
    ChangeThread threads[CHANGE_THREAD_NUM];
    volatile uint32_t stackSize;

    pthread_mutex_t mutex;
    pthread_cond_t readyCond;
    pthread_cond_t finishedCond;

    void doAction(const char *str, uint64_t length, uint64_t num, bool isAdd);

public:
    ChangePool(HashTable *tree);
    void add(const char *str, uint64_t length, uint64_t num);
    void remove(const char *str, uint64_t length, uint64_t num);
    void waitAllThreads();
    void threadIsReady(ChangeThread *thread);
};