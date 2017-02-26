//
// Created by opot on 26.02.17.
//

#include "ProcessingThread.h"

ProcessingThread::ProcessingThread(){
    state = FREE;
    pthread_create(&thread, NULL, routine, (void*)this);
    pthread_mutex_unlock(&queue_state);
    isEmpty = true;
}

void ProcessingThread::add(string &str){
    //pthread_mutex_lock(&queue_state);
    query.push({1, str});
    //pthread_mutex_unlock(&queue_state);
    isEmpty = false;
}

void ProcessingThread::remove(string &str) {
   // pthread_mutex_lock(&queue_state);
    query.push({-1, str});
    //pthread_mutex_unlock(&queue_state);
    isEmpty = false;
}

void ProcessingThread::process(string &text, int num){
   // pthread_mutex_lock(&queue_state);
    query.push({0, text});
   // pthread_mutex_unlock(&queue_state);
    isEmpty = false;
}

ThreadState ProcessingThread::getState(){
    return state;
}

int ProcessingThread::getNum(){
    return num;
}

void ProcessingThread::printResult(){
    puts(result.c_str());
    state = ThreadState::FREE;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void* ProcessingThread::routine(void* data){
    ProcessingThread *state = (ProcessingThread*)data;

    cout << "Started thread " << state->thread << endl;

    while(1){
        if(!state->isEmpty)
        if(pthread_mutex_lock(&state->queue_state)) {
           if (!state->query.empty()) {
               Query query = state->query.front();
               state->query.pop();
               if(state->query.empty())state->isEmpty = true;
               pthread_mutex_unlock(&state->queue_state);

               if(query.type == 1) {
                   state->ngrams.add(query.str);
                   continue;
               }

               if(query.type == -1) {
                   state->ngrams.remove(query.str);
                   continue;
               }

               state->result = state->ngrams.searchInText(query.str);
               state->state = ThreadState::OUT;

           } else {
               pthread_mutex_unlock(&state->queue_state);
           }
       }
    }
}
#pragma clang diagnostic pop