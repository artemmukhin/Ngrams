#include "SuffixList.h"

SuffixList::SuffixList()
        :
        head(nullptr)
{}

SuffixList::SuffixList(string &newSuffix) : head(new SuffixNode)
{
    head->str = newSuffix;
    head->hash = hash(newSuffix);
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
        node->next->hash = hash(newSuffix);
        node->next->next = tmp;
    }
        // insert after nullptr == insert before head
    else {
        SuffixNode *tmp = head;
        head = new SuffixNode;
        head->str = newSuffix;
        head->hash = hash(newSuffix);
        head->next = tmp;
    }
}

void SuffixList::remove(string &suffix)
{
    uint64_t hashOfSuffix = hash(suffix);
    SuffixNode *node = head;
    SuffixNode *prev = nullptr;
    while (node && node->hash != hashOfSuffix && node->str != suffix) {
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

uint64_t SuffixList::hash(string &s)
{
    const int MAX_LEN = 100000;
    const int P = 239017;
    uint64_t hashes[MAX_LEN + 1], powers[MAX_LEN + 1];

    powers[0] = 1;
    hashes[0] = 0;
    for (size_t i = 0; i < s.size(); i++) {
        hashes[i + 1] = hashes[i] * P + s[i];
        powers[i + 1] = powers[i] * P;
    }
    return hashes[s.size()];
}
