#include <math.h>
#include <string>
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
    friend class HashTable;
private:
    Node *root;

    void addHelper(Node *start, string &prefix, string &suffix);

    void printHelper(Node *start);

    bool removeHelper(Node *parent, Node *current, string &prefix, string &suffix);

public:
    NgramTree();

    void print();

    // void add(string &val);

    void add(string &prefix, string &suffix);

    // bool remove(string &val);

    bool remove(string &prefix, string &suffix);

    //const SuffixList *suffixesOf(string prefix) const;

    //string &searchInText(string text);
};
