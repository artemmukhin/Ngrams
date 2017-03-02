//
// Created by opot on 02.03.17.
//

#include "ResultPipe.h"

ResultPipe::ResultPipe(){
    state = ThreadState::FREE;
}

bool ResultPipe::isReady(int num){
    if(state == ThreadState::FREE){
        state = ThreadState::HOLD;
        pipe.push({NULL, num});
        return true;
    }
    return false;
}

void ResultPipe::Push(std::string* result){
    pipe.back().result = result;
    state = ThreadState::FREE;
}

bool ResultPipe::TryOut(int curr_num){
    if(pipe.empty()) return false;
    if(pipe.front().num == curr_num){
        if(pipe.front().result != NULL) {
            puts(pipe.front().result->c_str());
            pipe.pop();
            return true;
        }
    }
    return false;
}