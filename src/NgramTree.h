#include <math.h>
#include <string>
#include <vector>
#include <set>
#include "Node.h"

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


class NgramTree
{
private:
    Node *root;

    void addHelper(Node *start, string prefix, string suffix);

    void printHelper(Node *start);

    bool removeHelper(Node *parent, Node *current, string prefix, string suffix);

public:
    NgramTree();

    void add(string val);

    void print();

    bool remove(string prefix, string suffix);

    const list<string> *suffixesOf(string prefix) const;

    string searchInText(string text);
};
