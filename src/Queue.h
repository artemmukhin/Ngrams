#pragma once

#include <cstdint>
struct QueueNode
{
    const char *str;
    int length;
    int num;

    QueueNode *next;

    QueueNode(const char *str, uint64_t length, uint64_t num);
};

class Queue
{

    QueueNode *head;
    QueueNode *last;

public:
    Queue();

    void push(const char *str, uint64_t length, uint64_t num);
    bool isEmpty();
    QueueNode *pop();
};