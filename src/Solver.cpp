//
// Created by opot on 07.03.17.
//

#include "Solver.h"

Solver::Solver() : processor(&ngrams), change(&ngrams) {}

void Solver::add(const char *str, int length, int num) {
    change.add(str, length, num);
}

void Solver::remove(const char *str, int length, int num) {
    change.remove(str, length, num);
}

void Solver::solve(const char *str, int length, int num) {
    texts.push(str, length, num);
}

void Solver::flush() {
    change.wait();

    while(!texts.isEmpty()){
        QueueNode *data = texts.pop();
        processor.process(data->str, data->length, data->num);
    }

    //ngrams.clear();// TODO clear commented
    fflush(stdout);
}