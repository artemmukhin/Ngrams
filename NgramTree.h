#include <iostream>
#include <math.h>
#include <string>
#include <vector>
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
private:
    string prefix;
    vector<string> suffixes;

    Node *left;
    Node *right;

public:
    Node(string val)
    {
        this->prefix = val;
    }

    Node(string val, Node *left, Node *right)
    {
        this->prefix = val;
        this->left = left;
        this->right = right;
    }

    void addSuffix(string suff)
    {
        suffixes.push_back(suff);
    }

    void print()
    {
        cout << prefix << ":" << endl;
        for (int i = 0; i < suffixes.size(); i++)
            cout << "    " << prefix << suffixes[i] << endl;
    }

    string getPrefix()
    {
        return prefix;
    }

    Node *getLeft()
    {
        return left;
    }

    Node *getRight()
    {
        return right;
    }

    void setLeft(Node *newLeft)
    {
        left = newLeft;
    }

    void setRight(Node *newRight)
    {
        right = newRight;
    }
};

class NgramTree
{
private:
    Node *root;

    void addHelper(Node *start, string prefix, string suffix);

    void printHelper(Node *start);

    //bool removeHelper(Node *parent, Node *current, string prefix, string suffix);

public:
    NgramTree();

    void add(string val);

    void print();

    //bool remove(string val);
};
