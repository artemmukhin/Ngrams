//
// Created by opot on 07.03.17.
//

#include "Queue.h"

QueueNode::QueueNode(const char *str, int length, int num)
{
    this->str = str;
    this->length = length;
    this->num = num;
    this->next = nullptr;
}

Queue::Queue()
{
    head = nullptr;
    last = nullptr;
}

void Queue::push(const char *str, int length, int num)
{
    if (head == nullptr) {
        head = new QueueNode(str, length, num);
        last = head;
        return;
    }

    last->next = new QueueNode(str, length, num);
    last = last->next;
}

bool Queue::isEmpty()
{
    return head == nullptr;
}

QueueNode *Queue::pop()
{
    QueueNode *res = head;
    head = head->next;
    return res;
}