#include "ChangePool.h"

ChangePool::ChangePool(HashTable *tree)
{
    stackSize = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&readyCond, NULL);
    pthread_cond_init(&finishedCond, NULL);

    for (uint16_t i = 0; i < CHANGE_THREAD_NUM; i++) {
        threads[i].init(this, tree, i);
        threads[i].start();
        threadIsReady(&(threads[i]));
    }
}

void ChangePool::doAction(const char *str, uint64_t length, uint64_t num, bool isAdd){
    pthread_mutex_lock(&mutex);

    while (stackSize == 0)
        pthread_cond_wait(&readyCond, &mutex);

    ChangeThread *freeThread = threadStack[--stackSize];

    pthread_mutex_unlock(&mutex);

    freeThread->setAction(isAdd, str, length, num);
    //freeThread->signal();
}

void ChangePool::add(const char *str, uint64_t length, uint64_t num)
{
    doAction(str, length, num, true);
}

void ChangePool::remove(const char *str, uint64_t length, uint64_t num)
{
    doAction(str, length, num, false);
}

void ChangePool::threadIsReady(ChangeThread *readyThread)
{
    pthread_mutex_lock(&mutex);

    uint32_t index = stackSize++;
    threadStack[index] = readyThread;

    if (index == 0)
        pthread_cond_signal(&readyCond);

    pthread_mutex_unlock(&mutex);

    if (index == CHANGE_THREAD_NUM - 1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&finishedCond);
        pthread_mutex_unlock(&mutex);
    }
}

void ChangePool::waitAllThreads()
{
    pthread_mutex_lock(&mutex);
    while (stackSize < CHANGE_THREAD_NUM) {
        pthread_cond_wait(&finishedCond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

