//
// Created by opot on 07.03.17.
//

#include "Solver.h"

Solver::Solver() {
    change = new ChangePool(&ngrams);
}

void Solver::add(const char *str, int length, int num) {
    change->add(str, length, num);
}

void Solver::remove(const char *str, int length, int num) {
    change->remove(str, length, num);
}

void Solver::solve(const char *str, int length, int num) {
    texts.push(str, length, num);
}

void Solver::flush() {//TODO precess text query
    change->wait();


    ngrams.clear();
    fflush(stdout);
}