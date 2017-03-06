#pragma once

#include <string>
#include "HashFunctions.h"

using namespace std;

struct SuffixNode
{
    HString suffix;
    SuffixNode *next;
    bool isFound = false; // only for search
};

class SuffixList
{
private:
    SuffixNode *head;

public:
    SuffixList();
    SuffixList(const HString suffix);
    SuffixNode *getHead() const;
    void insert(SuffixNode *node, const HString suffix);
    void remove(const HString suffix);
};
