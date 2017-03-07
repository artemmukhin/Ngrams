//
// Created by opot on 07.03.17.
//

#include "ChangeThread.h"

ChangeThread::ChangeThread(HashTable *tree) {
    this->tree = tree;
    pthread_create(&thread, NULL, routine, (void *) this);
    pthread_cond_init(&wait, NULL);
    pthread_mutex_init(&mutex, NULL);
    isEmpty = true;
}

void ChangeThread::signal() {
    pthread_mutex_lock(&this->mutex);
    pthread_cond_signal(&this->wait);
    pthread_mutex_unlock(&this->mutex);
    isEmpty = false;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void* ChangeThread::routine(void *data) {

    ChangeThread* thread = (ChangeThread*) data;

    while(true) {
        pthread_mutex_lock(&thread->mutex);
        pthread_cond_wait(&thread->wait, &thread->mutex);

        if(thread->isAdd)
            thread->tree->add(thread->str, thread->length, thread->num);
        else
            thread->tree->remove(thread->str, thread->length, thread->num);

        thread->isEmpty = true;
        pthread_mutex_lock(&thread->mutex);
    }
}
#pragma clang diagnostic pop