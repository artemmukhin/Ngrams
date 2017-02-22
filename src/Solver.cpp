//
// Created by opot on 21.02.17.
//

#include "Solver.h"

#include <cstdlib>

Solver::Solver() {
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
}

void Solver::add(string& ngram, int num){
    ngrams.add(ngram, num);
}

void Solver::remove(string& ngram, int num){
    ngrams.remove(ngram, num);
}
void Solver::rebuild(){
    ngrams.clear();
}

void Solver::solve(string* texts, int* nums, int count) {

    int res;
    void * status;

    for (int i = 0; i < count; i++) {
        ThreadData *data = new ThreadData(&texts[i], nums[i], i, this);
        res = pthread_create(&threads[i], &attr, compute, (void*)data);
        if (res) {
            cout << "Error:unable to create thread," << res << endl;
            std::terminate();
        }
    }

    for (int i = 0; i < count; i++){
        res = pthread_join(threads[i], &status);
        if (res){
            cout << "Error:unable to join," << res << endl;
            std::terminate();
        }
        cout << result[i];
    }

    this->rebuild();

}
void* Solver::compute(void* data){
    vector<string> result;
    ThreadData *tdata = (ThreadData*)data;
    tdata->solver->ngrams.searchInText(*tdata->text, result, tdata->num);

    if(result.size() == 0) {
        tdata->solver->result[tdata->thread_num] = "-1";
        return NULL;
    }

    string res_str = "";

    for(int i = 0; i < result.size(); i++)
        if(res_str.size() == 0)
            res_str = result[i];
        else
            res_str += "|" + result[i];

    res_str += "\n";
    tdata->solver->result[tdata->thread_num] = res_str;
    //cout << "End thread " << tdata->thread_num << std::endl;
    delete tdata;
    pthread_exit(NULL);
}