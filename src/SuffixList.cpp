#include "SuffixList.h"


ChangeList::ChangeList()
    : head(nullptr),
      last(nullptr)
{}

ChangeNode *ChangeList::getHead() const
{
    return this->head;
}

void ChangeList::insert(ChangeNode *node, Change change)
{
    if (node) {
        ChangeNode *tmp = node->next;
        node->next = new ChangeNode;
        node->next->change = change;
        node->next->next = tmp;
    }
        // insert after nullptr == insert before head
    else {
        ChangeNode *tmp = head;
        head = new ChangeNode;
        head->change = change;
        head->next = tmp;
    }

}

void ChangeList::add(int num)
{
    ChangeNode *node = head;
    ChangeNode *prev = nullptr;
    while (node && node->change.num < num) {
        prev = node;
        node = node->next;
    }

    if (prev == this->last && prev != nullptr) {
        if (this->last->change.type != 1)
            this->insert(last, {1, num});
        return;
    }

    this->insert(prev, {1, num});
}

void ChangeList::remove(int num)
{
    ChangeNode *node = head;
    ChangeNode *prev = nullptr;
    while (node && node->change.num < num) {
        prev = node;
        node = node->next;
    }

    if (prev == this->last && prev != nullptr) {
        if (this->last->change.type != -1)
            this->insert(last, {-1, num});
        return;
    }

    this->insert(prev, {-1, num});
}

int ChangeList::lastChangeBefore(int num)
{
    if (head == nullptr)
        return -1;

    ChangeNode *node = head;
    ChangeNode *prev = nullptr;
    while (node && node->change.num < num) {
        prev = node;
        node = node->next;
    }

    if (prev == nullptr)
        return -1;

    //head = prev; // "remove" changes before this last change
    return prev->change.type;
}


void SuffixNode::add(int num)
{
    changes.add(num);
}

void SuffixNode::remove(int num)
{
    changes.remove(num);
}

int SuffixNode::lastChangeBefore(int num)
{
    return changes.lastChangeBefore(num);
}

SuffixList::SuffixList()
    : head(nullptr)
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

void SuffixList::insert(SuffixNode *node, const HString suffix, int num)
{
    if (node) {
        SuffixNode *tmp = node->next;
        node->next = new SuffixNode;
        node->next->suffix = suffix;
        node->next->next = tmp;
        node->next->add(num);
    }
        // insert after nullptr == insert before head
    else {
        SuffixNode *tmp = head;
        head = new SuffixNode;
        head->suffix = suffix;
        head->next = tmp;
        head->add(num);
    }
}

void SuffixList::remove(const HString suffix, int num)
{
    SuffixNode *node = head;
    SuffixNode *prev = nullptr;
    while (node) {
        if (HashEngine::isEqual(node->suffix, suffix))
            break;

        prev = node;
        node = node->next;
    }

    if ((node && prev) || (node == head && node != nullptr))
        node->remove(num);
}
