#include "NgramTree.h"

NgramTree::NgramTree()
    :
    root(nullptr)
{}

void NgramTree::addHelper(Node *start, const HString prefix, const HString suffix, int num)
{
    if (HashEngine::isEqual(start->prefix, prefix))
        start->addSuffix(suffix, num);

    else if (start->prefix.hash > prefix.hash) {
        if (!start->left) {
            start->left = new Node(prefix);
            start->left->addSuffix(suffix, num);
        }
        else
            addHelper(start->left, prefix, suffix, num);
    }
    else {
        if (!start->right) {
            start->right = new Node(prefix);
            start->right->addSuffix(suffix, num);
        }
        else
            addHelper(start->right, prefix, suffix, num);
    }
}

void NgramTree::add(const HString prefix, const HString suffix, int num)
{
    if (root) {
        addHelper(root, prefix, suffix, num);
    }
    else {
        root = new Node(prefix);
        root->addSuffix(suffix, num);
    }
}

bool NgramTree::removeHelper(Node *parent, Node *current, const HString prefix, const HString suffix, int num)
{
    if (!current)
        return false;

    if (HashEngine::isEqual(current->prefix, prefix)) {
        current->removeSuffix(suffix, num);
        return true;
    }

    return removeHelper(current, current->left, prefix, suffix, num) ||
        removeHelper(current, current->right, prefix, suffix, num);
}

bool NgramTree::remove(const HString prefix, const HString suffix, int num)
{
    return this->removeHelper(nullptr, this->root, prefix, suffix, num);
}