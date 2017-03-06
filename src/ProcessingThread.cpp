#include "ProcessingThread.h"

ProcessingThread::ProcessingThread()
{
    pthread_create(&thread, NULL, routine, (void *) this);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void *ProcessingThread::routine(void *data)
{
    ProcessingThread *state = (ProcessingThread *) data;

    //cout << "Started thread " << state->thread << endl;

    while (1) {
        Query query = state->pipe.next();

        //cout << "Thread " << state->thread << ". Processing \"{"  << query.type << " " << query.str << "}\"\n";

        if (query.type == 1) {
            state->ngrams.add(query.str, query.length);
            continue;
        }

        if (query.type == -1) {
            state->ngrams.remove(query.str, query.length);
            continue;
        }

        state->result.Push(state->ngrams.searchInText(query.str, query.length));
    }
}

#pragma clang diagnostic pop