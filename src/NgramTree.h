#pragma once

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

    void addHelper(Node *start, const HString prefix, const HString suffix, int num);

    bool removeHelper(Node *parent, Node *current, const HString prefix, const HString suffix, int num);

public:
    NgramTree();

    void add(const HString prefix, const HString suffix, int num);

    bool remove(const HString prefix, const HString suffix, int num);
};
