#include "SuffixList.h"

void SuffixNode::add(int num) {//TODO check for correct

    if(this->chanages.empty()){
        this->chanages.push_back({1, num});
        return;
    }

    auto it = this->chanages.begin();
    while(it != this->chanages.end() && (*it).num < num)
        it++;

    if(it == this->chanages.end()){
        if(this->chanages.back().type != 1)
            this->chanages.push_back({1, num});
        return;
    }

    it++;
    this->chanages.emplace(it);
    *it = {1, num};
}

void SuffixNode::remove(int num) {//TODO check for correct

    auto it = this->chanages.begin();
    while(it != this->chanages.end() && (*it).num < num)
        it++;

    if(it == this->chanages.end()){
        if(this->chanages.back().type != 0)
            this->chanages.push_back({0, num});
        return;
    }

    it++;
    this->chanages.emplace(it);
    *it = {0, num};
}

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

void SuffixList::insert(SuffixNode *node, const HString suffix, int num)
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

    node->add(num);

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

    if (node && prev || node == head)
        node->remove(num);

}