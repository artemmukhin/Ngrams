//
// Created by opot on 26.02.17.
//

#include "Solver.h"

#include <chrono>
#include <thread>

Solver::Solver(){
    waitOut = 0;
    total = 0;
}

void Solver::add(string &str){
    for(int i = 0; i < THREAD_NUM; i++)
        thread[i].pipe.add(str);
}

void Solver::remove(string &str){
    for(int i = 0; i < THREAD_NUM; i++)
        thread[i].pipe.remove(str);

}

void Solver::flush() {
    while(waitOut != total) {
        for (int i = 0; i < THREAD_NUM; i++)
            if(thread[i].num == waitOut){
                while(thread[i].state != ThreadState::OUT);
                thread[i].printResult();
                waitOut++;
            }
    }

}

void Solver::wait(){
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    /*for(int i = 0; count != THREAD_NUM; i++) {
        pthread_mutex_lock(&thread[i].queue_state);
        if(thread[i].query.empty()) count++;
        else i--;
        pthread_mutex_unlock(&thread[i].queue_state);
    }*/
}

void Solver::process(string &text, int num){
    int i = 0;
    total++;
    while(1) {
        if (thread[i].state == ThreadState ::OUT)
            if(thread[i].getNum() == waitOut){
                waitOut++;
                thread[i].printResult();
            }

            if(thread[i].state == ThreadState::FREE){
                //scout << "Query given to " << i << " thread" << endl;
                thread[i].pipe.process(text);
                thread[i].state = ThreadState ::HOLD;
                thread[i].num = num;
                break;
            }

        i++;
    }
}