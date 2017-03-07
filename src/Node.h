#pragma once

#include <iostream>
#include <string>
#include "SuffixList.h"

using namespace std;

class Node
{
    friend class NgramTree;
    friend class HashTable;

private:
    const HString prefix;
    SuffixList suffixes;

    Node *left;
    Node *right;

public:
    Node(const HString prefix);

    Node(const HString prefix, Node *left, Node *right);

    void addSuffix(const HString suffix, int num);

    void removeSuffix(const HString suffix, int num);
};

