#include "NgramTree.h"

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

bool stringCompare(const Suffix &left, const Suffix &right)
{
    return left.suffix.size() < right.suffix.size();
}

void Node::addSuffix(string suff, int num)
{
    for(int i = 0; i < suffixes.size(); i++)
        if(suffixes[i].suffix == suff){
            suffixes[i].actions.push_back({num, 1});
            return;
        }

    vector<Suffix::Action> acts;
    suffixes.push_back({suff, acts});
    suffixes[suffixes.size() - 1].actions.push_back({num, 1});
    std::sort(suffixes.begin(), suffixes.end(), stringCompare);
}

void Node::removeSuffix(string suff, int num)
{
    for(int i = 0; i < suffixes.size(); i++)
        if(suffixes[i].suffix == suff){
            suffixes[i].actions.push_back({num, -1});
            return;
        }
}

void Node::clear() {
    if()
}

NgramTree::NgramTree()
{
    root = nullptr;
}

void NgramTree::addHelper(Node *start, string prefix, string suffix, int num)
{
    if (start->prefix == prefix) {
        start->addSuffix(suffix, num);
    }

    else if (start->prefix.compare(prefix) > 0) {
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

void NgramTree::add(string &val, int num)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    if (root) {
        this->addHelper(root, prefix, suffix, num);
    }
    else {
        root = new Node(prefix);
        root->addSuffix(suffix, num);
    }
}

void NgramTree::removeHelper(Node *parent, Node *current, string prefix, string suffix, int num)
{
    // Если в узле всего один суффикс, то можно либо полностью удалить узел,
    // либо оставить его (получится узел без суффиксов). Пока оставил второй вариант

    if (!current)
        return;

    if (current->prefix == prefix) {
        current->removeSuffix(suffix, num);
        return;
    }

    removeHelper(current, current->left, prefix, suffix, num);
    removeHelper(current, current->right, prefix, suffix, num);
}

void NgramTree::remove(string &val, int num)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    this->removeHelper(nullptr, this->root, val.substr(0, i), val.substr(i, val.length()), num);
}

void NgramTree::clear() {
    root->clear();
}

const vector<Suffix> *NgramTree::suffixesOf(string prefix) const
{
    Node *current = this->root;
    while (current) {
        if (current->prefix == prefix && current->suffixes.size() > 0)
            return &current->suffixes;
        if (current->prefix > prefix)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void NgramTree::searchInText(string &text, vector<string> &result, int num)
{
    size_t i = 0;
    string currWord = "";
    const vector<Suffix> *suffixes;
    set<const string *> foundStrings;


    while (i <= text.length()) {
        if (text[i] == ' ' || i == text.length()) {
            suffixes = this->suffixesOf(currWord);
            if (suffixes) {
                for (size_t it = 0; it < suffixes->size(); it++) {
                    if (foundStrings.find(&((*suffixes)[it]).suffix) != foundStrings.end())
                        continue;
                    bool flag = true;
                    size_t j;
                    for (j = 0; j < (*suffixes)[it].suffix.length(); j++) {
                        if (text[i + j] != (*suffixes)[it].suffix[j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (text[i + j] != ' ' && (i + j) != text.length())
                        flag = false;
                    if (flag) {
                        bool isAlive = true;
                        for(int actions = 0; actions < (*suffixes)[it].actions.size(); actions++)
                            if((*suffixes)[it].actions[actions].num < num)
                                isAlive = (*suffixes)[it].actions[actions].action == 1;
                            else
                                break;
                        if (isAlive) {
                            foundStrings.insert(&(*suffixes)[it].suffix);
                            result.push_back(currWord + (*suffixes)[it].suffix);
                        }
                    }
                }
            }
            currWord = "";
            i++;
        }
        currWord += text[i++];
    }
}
