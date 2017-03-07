#include "Node.h"

Node::Node(const HString prefix)
    :
    prefix(prefix),
    left(nullptr),
    right(nullptr),
    suffixes()
{}

Node::Node(const HString prefix, Node *left, Node *right)
    :
    prefix(prefix),
    left(left),
    right(right),
    suffixes()
{}

void Node::addSuffix(const HString suffix, int num)//TODO suffix history
{
    SuffixNode *node = suffixes.getHead();
    SuffixNode *prev = nullptr;
    while (node && node->suffix.length <= suffix.length) {
        // exit, if suff already exists
        if (HashEngine::isEqual(node->suffix, suffix))
            return;

        prev = node;
        node = node->next;
    }
    suffixes.insert(prev, suffix);
}

void Node::removeSuffix(const HString suffix, int num)//TODO suffix history
{
    suffixes.remove(suffix);
}