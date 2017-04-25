#include "ChangeThread.h"
#include "ChangePool.h"

ChangeThread::ChangeThread()
{
    pthread_cond_init(&readyCond, NULL);
    pthread_mutex_init(&mutex, NULL);
    actionIsReady = false;
}

/*
ChangeThread::ChangeThread(HashTable *tree)
{
    isEmpty = true;
    this->tree = tree;
    pthread_cond_init(&wait, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread, NULL, routine, (void *) this);
}
*/

/*
void ChangeThread::signal()
{
    pthread_mutex_lock(&this->mutex);
    pthread_cond_signal(&this->readyCond);
    pthread_mutex_unlock(&this->mutex);
}
*/

void ChangeThread::init(ChangePool *pool, HashTable *tree, uint16_t id)
{
    this->pool = pool;
    this->tree = tree;
    this->ID = id;
}

void ChangeThread::setAction(bool isAdd, const char *str, uint64_t length, uint64_t num)
{
    pthread_mutex_lock(&mutex);

    this->isAdd = isAdd;
    this->str = str;
    this->length = length;
    this->num = num;
    actionIsReady = true;
    pthread_cond_signal(&readyCond);

    pthread_mutex_unlock(&mutex);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void ChangeThread::routine()
{
    while (true) {
        pthread_mutex_lock(&mutex);
        while (!actionIsReady) {
            pthread_cond_wait(&readyCond, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        if (isAdd)
            tree->add(str, length, num);
        else
            tree->remove(str, length, num);

        actionIsReady = false;
        pool->threadIsReady(this);
    }
}

void *ChangeThread::threadFunction(void *data)
{
    ChangeThread *thread = (ChangeThread *) data;
    thread->routine();
    pthread_exit(nullptr);
}
#pragma clang diagnostic pop

void ChangeThread::start()
{
    pthread_create(&thread, NULL, threadFunction, (void *) this);
}


/*
void *ChangeThread::routine(void *data)
{
    ChangeThread *thread = (ChangeThread *) data;

    //cout << "Thread init " << thread->thread << endl;

    while (true) {
        // std::cout << "wait for signal...\n";
        pthread_mutex_lock(&thread->mutex);
        while (thread->isEmpty) {
            pthread_cond_wait(&thread->wait, &thread->mutex);
        }
        // cout << "wake up " << thread->thread << endl;

        if (thread->isAdd)
            thread->tree->add(thread->str, thread->length, thread->num);
        else
            thread->tree->remove(thread->str, thread->length, thread->num);

        pthread_mutex_lock(thread->poolMutex);
        thread->isEmpty = true;

        //cout << "routine " << thread->numberOfChangeTread << ": signal to finish" << endl;
        pthread_cond_signal(thread->poolCond);

        pthread_mutex_unlock(&thread->mutex);
        pthread_mutex_unlock(thread->poolMutex);
    }
    return nullptr;
}
*/