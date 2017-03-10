//
// Created by opot on 07.03.17.
//

#include "ChangeThread.h"

ChangeThread::ChangeThread()
    : isEmpty(true)
{
    pthread_cond_init(&wait, NULL);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread, NULL, routine, (void *) this);
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

void ChangeThread::setTree(HashTable *tree)
{
    this->tree = tree;
}

void ChangeThread::signal()
{
    // std::cout << "signal\n";
    isEmpty = false;
    pthread_mutex_lock(&this->mutex);
    pthread_cond_signal(&this->wait);
    pthread_mutex_unlock(&this->mutex);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *ChangeThread::routine(void *data)
{

    ChangeThread *thread = (ChangeThread *) data;

    cout << "Thread init " << thread->thread << endl;

    while (true) {
        pthread_mutex_lock(&thread->mutex);
        // std::cout << "wait for signal...\n";
        while (thread->isEmpty) {
            pthread_cond_wait(&thread->wait, &thread->mutex);
        }

        // cout << "wake up " << thread->thread << endl;

        if (thread->isAdd)
            thread->tree->add(thread->str, thread->length, thread->num);
        else
            thread->tree->remove(thread->str, thread->length, thread->num);

        thread->isEmpty = true;
        pthread_mutex_unlock(&thread->mutex);
    }
}

#pragma clang diagnostic pop