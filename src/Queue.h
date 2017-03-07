//
// Created by opot on 07.03.17.
//

#ifndef NGRAMS_QUEUE_H
#define NGRAMS_QUEUE_H

struct QueueNode {
    const char* str;
    int length;
    int num;

    QueueNode* next;

    QueueNode(const char* str, int length, int num);
};

class Queue {

    QueueNode *head;
    QueueNode *last;

public:
    Queue();

    void push(const char* str, int length, int num);
    bool isEmpty();
    QueueNode* pop();
};


#endif //NGRAMS_QUEUE_H
