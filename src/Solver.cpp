//
// Created by opot on 26.02.17.
//

#include "Solver.h"

Solver::Solver(){
    waitOut = 0;
}

void Solver::add(string &str){
    for(int i = 0; i < THREAD_NUM; i++)
        thread[i].add(str);
}

void Solver::remove(string &str){
    for(int i = 0; i < THREAD_NUM; i++)
        thread[i].remove(str);

}

void Solver::wait(){
    int count = 0;
    cout << "Waiting" << endl;
    for(int i = 0; count != THREAD_NUM; i++) {
       // pthread_mutex_lock(&thread[i].queue_state);
        if(thread[i].query.empty()) count++;
        else i--;
       // pthread_mutex_unlock(&thread[i].queue_state);
    }
}

void Solver::process(string &text, int num){
    int i = 0;
    while(1) {
        if (thread[i].getState() == ThreadState ::OUT)
            if(thread[i].getNum() == waitOut){
                waitOut++;
                thread[i].printResult();
            }

            if(thread[i].getState() == ThreadState::FREE){
                cout << "Query given to " << i << " thread" << endl;
                thread[i].process(text, num);
                break;
            }

        i++;
    }
}