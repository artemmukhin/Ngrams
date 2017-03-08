#include "Node.h"

Node::Node(const HString prefix)
    :
    prefix(prefix),
    left(nullptr),
    right(nullptr),
    suffixes()
{
    pthread_mutex_init(&mutex, NULL);
}

Node::Node(const HString prefix, Node *left, Node *right)
    :
    prefix(prefix),
    left(left),
    right(right),
    suffixes()
{
    pthread_mutex_init(&mutex, NULL);
}

void Node::addSuffix(const HString suffix, int num)
{

    pthread_mutex_lock(&mutex);

    SuffixNode *node = suffixes.getHead();
    SuffixNode *prev = nullptr;
    while (node && node->suffix.length <= suffix.length) {
        // exit, if suff already exists
        if (HashEngine::isEqual(node->suffix, suffix))
            node->add(num);

        prev = node;
        node = node->next;
    }
    suffixes.insert(prev, suffix, num);

    pthread_mutex_unlock(&mutex);
}

void Node::removeSuffix(const HString suffix, int num)
{
    pthread_mutex_lock(&mutex);
    suffixes.remove(suffix, num);
    pthread_mutex_unlock(&mutex);
}