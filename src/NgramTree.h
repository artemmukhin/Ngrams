#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
earth a b c
director
health director
health


                                         |-----prefix="director",suffixes=[""]
                                         |
prefix="earth",suffixes=["a b c"]--------|
                                         |
                                         |-----prefix="health",suffixes=["director", ""]

*/

class Node
{
    friend class NgramTree;

private:
    string prefix;
    vector<string> suffixes;

    Node *left;
    Node *right;

public:
    Node(string val);

    Node(string val, Node *left, Node *right);

    void print() const;

    void addSuffix(string suff);

    void removeSuffix(string suff);

    void swapWithNode(Node *other);
};

class NgramTree
{
private:
    Node *root;

    void addHelper(Node *start, string prefix, string suffix);

    void printHelper(Node *start);

    bool removeHelper(Node *parent, Node *current, string prefix, string suffix);

public:
    NgramTree();

    void add(string &val);

    void print();

    bool remove(string &val);

    const vector<string> *suffixesOf(string prefix) const;

    void searchInText(string &text, vector<string> &result);
};
