#include "NgramTree.h"

NgramTree::NgramTree()
    :
    root(nullptr)
{}

void NgramTree::addHelper(Node *start, const HString prefix, const HString suffix)
{
    if (start->prefix.hash == prefix.hash) {
        if (strcmp(start->prefix.str, prefix.str) == 0)
        start->addSuffix(suffix);
    }
    else if (start->prefix.str > prefix.str) {
        if (!start->left) {
            start->left = new Node(prefix);
            start->left->addSuffix(suffix);
        }
        else
            addHelper(start->left, prefix, suffix);
    }
    else {
        if (!start->right) {
            start->right = new Node(prefix);
            start->right->addSuffix(suffix);
        }
        else
            addHelper(start->right, prefix, suffix);
    }
}

void NgramTree::add(const HString prefix, const HString suffix)
{
    if (root) {
        addHelper(root, prefix, suffix);
    }
    else {
        root = new Node(prefix);
        root->addSuffix(suffix);
    }
}

bool NgramTree::removeHelper(Node *parent, Node *current, const HString prefix, const HString suffix)
{
    if (!current)
        return false;

    if (current->prefix.hash == prefix.hash) {
        if (strcmp(current->prefix.str, prefix.str) == 0) {
            current->removeSuffix(suffix);
            return true;
        }
    }

    return removeHelper(current, current->left, prefix, suffix) ||
        removeHelper(current, current->right, prefix, suffix);
}

bool NgramTree::remove(const HString prefix, const HString suffix)
{
    return this->removeHelper(nullptr, this->root, prefix, suffix);
}