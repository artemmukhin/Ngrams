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

struct Suffix{

    struct Action{
        int num;
        int action;
    };
    string suffix;
    vector<Action> actions;
};

class Node
{
    friend class NgramTree;

private:
    string prefix;
    vector<Suffix> suffixes;

    Node *left;
    Node *right;

public:
    Node(string val);
    Node(string val, Node *left, Node *right);

    void addSuffix(string suff, int num);
    void removeSuffix(string suff, int num);
    void clear();
};

class NgramTree
{
private:
    Node *root;

    void addHelper(Node *start, string prefix, string suffix, int num);
    void removeHelper(Node *parent, Node *current, string prefix, string suffix, int num);

public:
    NgramTree();

    void add(string &val, int num);
    void remove(string &val, int num);
    void clear();

    const vector<Suffix> *suffixesOf(string prefix) const;
    void searchInText(string &text, vector<string> &result, int num);
};
