#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class Node
{
    friend class NgramTree;

private:
    string prefix;
    list<string> suffixes;

    Node *left;
    Node *right;

public:
    Node(string val);

    Node(string val, Node *left, Node *right);

    void print() const;

    void addSuffix(string suff);

    void removeSuffix(string suff);
};
