#include "Node.h"

Node::Node(string val)
        :
        prefix(val),
        left(nullptr),
        right(nullptr),
        suffixes()
{}

Node::Node(string val, Node *left, Node *right)
        :
        prefix(val),
        left(left),
        right(right),
        suffixes()
{}

void Node::print() const
{
    cout << prefix << ":" << endl;
    SuffixNode *node = suffixes.getHead();
    while (node) {
        cout << "    " << node->str << endl;
        node = node->next;
    }
}

/*
inline bool stringCompare(const string &left, const string &right)
{
    return left.size() < right.size();
}
*/

void Node::addSuffix(string &suff)
{
    SuffixNode *node = suffixes.getHead();
    SuffixNode *prev = nullptr;
    while (node && node->str.size() <= suff.size()) {
        // exit, if suff already exists
        if (node->str == suff)
            return;
        prev = node;
        node = node->next;
    }
    suffixes.insert(prev, suff);
}

void Node::removeSuffix(string &suff)
{
    suffixes.remove(suff);
}