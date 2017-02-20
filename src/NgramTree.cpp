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

void Node::print() const
{
    cout << prefix << ":" << endl;
    for (int i = 0; i < suffixes.size(); i++)
        cout << "    " << prefix << suffixes[i] << endl;
}

bool stringCompare(const string &left, const string &right)
{
    return left.size() < right.size();
}

void Node::addSuffix(string suff)
{
    suffixes.push_back(suff);
    std::sort(suffixes.begin(), suffixes.end(), stringCompare);
}

void Node::removeSuffix(string suff)
{
    suffixes.erase(std::remove(suffixes.begin(), suffixes.end(), suff), suffixes.end());
}

void Node::swapWithNode(Node *other)
{
    string tempPrefix = this->prefix;
    vector<string> tempSuffixes = this->suffixes;

}

NgramTree::NgramTree()
{
    root = nullptr;
}

void NgramTree::addHelper(Node *start, string prefix, string suffix)
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

void NgramTree::add(string val)
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

bool NgramTree::removeHelper(Node *parent, Node *current, string prefix, string suffix)
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

bool NgramTree::remove(string prefix, string suffix)
{
    return this->removeHelper(nullptr, this->root, prefix, suffix);
}

const vector<string> *NgramTree::suffixesOf(string prefix) const
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

string NgramTree::searchInText(string text)
{
    size_t i = 0;
    string currWord = "";
    string result = "";
    const vector<string> *suffixes;
    set<const string *> foundStrings;


    while (i <= text.length()) {
        if (text[i] == ' ' || i == text.length()) {
            suffixes = this->suffixesOf(currWord);
            if (suffixes) {
                for (size_t it = 0; it < suffixes->size(); it++) {
                    if (foundStrings.find(&((*suffixes)[it])) != foundStrings.end())
                        continue;
                    bool flag = true;
                    size_t j;
                    for (j = 0; j < (*suffixes)[it].length(); j++) {
                        if (text[i + j] != (*suffixes)[it][j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (text[i + j] != ' ' && (i + j) != text.length())
                        flag = false;
                    if (flag) {
                        foundStrings.insert(&(*suffixes)[it]);
                        result += currWord + (*suffixes)[it] + "|";
                    }
                }
            }
            currWord = "";
            i++;
        }
        currWord += text[i++];
    }

    if (result != "")
        result.pop_back();
    else
        result = "-1";
    return result;
}
