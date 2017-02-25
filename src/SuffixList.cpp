#include "SuffixList.h"

SuffixList::SuffixList()
    :
    head(nullptr)
{}

SuffixList::SuffixList(string &newSuffix) : head(new SuffixNode)
{
    head->str = newSuffix;
    head->next = nullptr;
}

SuffixNode *SuffixList::getHead() const
{
    return this->head;
}

void SuffixList::insert(SuffixNode *node, string &newSuffix)
{
    if (node) {
        SuffixNode *tmp = node->next;
        node->next = new SuffixNode;
        node->next->str = newSuffix;
        node->next->next = tmp;
    }
        // insert after nullptr == insert before head
    else {
        SuffixNode *tmp = head;
        head = new SuffixNode;
        head->str = newSuffix;
        head->next = tmp;
    }
}

void SuffixList::remove(string &suffix)
{
    SuffixNode *node = head;
    SuffixNode *prev = nullptr;
    while (node && node->str != suffix) {
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
