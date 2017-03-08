#pragma once

#include <iostream>
#include <string>
#include <pthread.h>

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

    pthread_mutex_t mutex;

public:
    Node(const HString prefix);

    Node(const HString prefix, Node *left, Node *right);

    void addSuffix(const HString suffix, int num);

    void removeSuffix(const HString suffix, int num);
};

