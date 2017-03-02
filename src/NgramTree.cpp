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

/*
void NgramTree::add(string &val)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    if (root) {
        this->addHelper(root, prefix, suffix);
    }
    else {
        root = new Node(prefix);
        root->addSuffix(suffix);
    }
}
*/

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

void NgramTree::printHelper(Node *start)
{
    if (!start)
        return;
    printHelper(start->left);
    start->print();
    printHelper(start->right);
}

void NgramTree::print()
{
    printHelper(this->root);
}

bool NgramTree::removeHelper(Node *parent, Node *current, string &prefix, string &suffix)
{
    // Если в узле всего один суффикс, то можно либо полностью удалить узел,
    // либо оставить его (получится узел без суффиксов). Пока оставил второй вариант

    if (!current)
        return false;

    if (current->prefix == prefix) {
        current->removeSuffix(suffix);
        return true;
    }

    return removeHelper(current, current->left, prefix, suffix) ||
           removeHelper(current, current->right, prefix, suffix);
}

/*
bool NgramTree::remove(string &val)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    return this->removeHelper(nullptr, this->root, prefix, suffix);
}
*/
bool NgramTree::remove(string &prefix, string &suffix)
{
    return this->removeHelper(nullptr, this->root, prefix, suffix);
}

