//
// Created by opot on 26.02.17.
//

#include "ProcessingThread.h"

ProcessingThread::ProcessingThread(){
    state = FREE;
    pthread_create(&thread, NULL, routine, (void*)this);
}

int ProcessingThread::getNum(){
    return num;
}

void ProcessingThread::printResult(){
    puts(result.c_str());
    //fflush(stdout)
    state = ThreadState::FREE;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void* ProcessingThread::routine(void* data){
    ProcessingThread *state = (ProcessingThread*)data;

    //cout << "Started thread " << state->thread << endl;

    while(1){
        Query query = state->pipe.next();

        //cout << "Thread " << state->thread << ". Processing \"{"  << query.type << " " << query.str << "}\"\n";

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

    }
}
#pragma clang diagnostic pop