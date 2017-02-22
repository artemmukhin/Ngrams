#include "Node.h"

Node::Node(string val)
{
    this->prefix = val;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(string val, Node *left, Node *right)
{
    this->prefix = val;
    this->left = left;
    this->right = right;
}

void Node::print() const
{
    cout << prefix << ":" << endl;
    for (auto it = suffixes.begin(); it != suffixes.end(); it++)
        cout << "    " << *it << endl;
}

inline bool stringCompare(const string &left, const string &right)
{
    return left.size() < right.size();
}

void Node::addSuffix(string suff)
{
    auto insertIt = std::lower_bound(suffixes.begin(), suffixes.end(), suff, stringCompare);
    suffixes.insert(insertIt, suff);
}

void Node::removeSuffix(string suff)
{
    auto findIt = find(suffixes.begin(), suffixes.end(), suff);
    suffixes.erase(findIt);
}