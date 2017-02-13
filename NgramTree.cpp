#include "NgramTree.h"

NgramTree::NgramTree()
{
    root = nullptr;
}

void NgramTree::addHelper(Node *start, string prefix, string suffix)
{
    if (start->getPrefix().compare(prefix) == 0) {
        start->addSuffix(suffix);
    }

    else if (start->getPrefix().compare(prefix) > 0) {
        if (!start->getLeft()) {
            start->setLeft(new Node(prefix));
            start->getLeft()->addSuffix(suffix);
        }
        else
            addHelper(start->getLeft(), prefix, suffix);
    }
    else {
        if (!start->getRight()) {
            start->setRight(new Node(prefix));
            start->getRight()->addSuffix(suffix);
        }
        else
            addHelper(start->getRight(), prefix, suffix);
    }
}

void NgramTree::add(string val)
{
    string prefix;
    string suffix;
    int i;
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

void NgramTree::printHelper(Node *start)
{
    if (!start)
        return;
    printHelper(start->getLeft());
    start->print();
    printHelper(start->getRight());
}

void NgramTree::print()
{
    printHelper(this->root);
}


/*
bool NgramTree::removeHelper(Node *parent, Node *current, string prefix, string suffix) {
    if (!current)
        return false;
    if (current->getPrefix() == prefix) {
        if (current->getLeft() == nullptr || current->getRight() == nullptr) {
            Node *temp = current->getLeft();
            if (current->getRight())
                temp = current->getRight();
            if (parent) {
                if (parent->getRight() == current) {
                    parent->setLeft(temp);
                }
                else {
                    parent->setRight(temp);
                }
            }
            else {
                this->root = temp;
            }
        }
        else {
            Node *validSubs = current->getRight();
            while (validSubs->getLeft()) {
                validSubs = validSubs->getLeft();
            }
            string temp = current->value;
            current->value = validSubs->value;
            validSubs->value = temp;
            return deleteValueHelper(current, current->right, temp);
        }
        delete current;
        return true;
    }
    return deleteValueHelper(current, current->left, value) ||
           deleteValueHelper(current, current->right, value);
}


bool NgramTree::remove(string value) {
    return this->deleteValueHelper(NULL, this->root, value);
}
*/