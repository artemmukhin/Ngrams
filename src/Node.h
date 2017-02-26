#include <iostream>
#include <string>
#include "SuffixList.h"
using namespace std;

class Node
{
    friend class NgramTree;
    friend class HashTable;

private:
    string prefix;
    SuffixList suffixes;

    Node *left;
    Node *right;

public:
    Node(string val);

    Node(string val, Node *left, Node *right);

    void addSuffix(string &suff);

    void removeSuffix(string &suff);
};

