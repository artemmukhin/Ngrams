#include "SuffixList.h"

SuffixList::SuffixList()
    :
    head(nullptr)
{}

SuffixList::SuffixList(const HString suffix)
    : head(new SuffixNode)
{
    head->suffix = suffix;
    head->next = nullptr;
}

SuffixNode *SuffixList::getHead() const
{
    return this->head;
}

void SuffixList::insert(SuffixNode *node, const HString suffix)
{
    if (node) {
        SuffixNode *tmp = node->next;
        node->next = new SuffixNode;
        node->next->suffix = suffix;
        node->next->next = tmp;
    }
        // insert after nullptr == insert before head
    else {
        SuffixNode *tmp = head;
        head = new SuffixNode;
        head->suffix = suffix;
        head->next = tmp;
    }
}

void SuffixList::remove(const HString suffix)
{
    SuffixNode *node = head;
    SuffixNode *prev = nullptr;
    while (node) {
        if (node->suffix.hash == suffix.hash) {
            //if (strcmp(node->suffix.str, suffix.str) == 0)
                break;
        }
        prev = node;
        node = node->next;
    }
    if (node && prev) {
        prev->next = node->next;
    }
    else if (node == head) {
        this->head = head->next;
    }
}