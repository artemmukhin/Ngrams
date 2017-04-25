#include "Queue.h"

QueueNode::QueueNode(const char *str, uint64_t length, uint64_t num)
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

void Queue::push(const char *str, uint64_t length, uint64_t num)
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