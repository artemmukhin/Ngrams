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

void Node::addSuffix(const HString suffix)
{
    SuffixNode *node = suffixes.getHead();
    SuffixNode *prev = nullptr;
    while (node && node->suffix.length <= suffix.length) {
        // exit, if suff already exists
        if (node->suffix.hash == suffix.hash) {
            if (strcmp(node->suffix.str, suffix.str) == 0)
                return;
        }
        prev = node;
        node = node->next;
    }
    suffixes.insert(prev, suffix);
}

void Node::removeSuffix(const HString suffix)
{
    suffixes.remove(suffix);
}