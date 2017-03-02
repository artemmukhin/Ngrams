#include "NgramTree.h"

NgramTree::NgramTree()
        :
        root(nullptr)
{}

void NgramTree::addHelper(Node *start, string &prefix, string &suffix)
{
    if (start->prefix == prefix) {
        start->addSuffix(suffix);
    }

    else if (start->prefix.compare(prefix) > 0) {
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

void NgramTree::add(string &prefix, string &suffix)
{
    if (root) {
        this->addHelper(root, prefix, suffix);
    }
    else {
        root = new Node(prefix);
        root->addSuffix(suffix);
    }
}

bool NgramTree::removeHelper(Node *parent, Node *current, string &prefix, string &suffix)
{
 if (!current)
        return false;

    if (current->prefix == prefix) {
        current->removeSuffix(suffix);
        return true;
    }

    return removeHelper(current, current->left, prefix, suffix) ||
           removeHelper(current, current->right, prefix, suffix);
}

bool NgramTree::remove(string &prefix, string &suffix)
{
    return this->removeHelper(nullptr, this->root, prefix, suffix);
}