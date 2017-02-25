#include "HashTable.h"

HashTable::HashTable()
{
    for (uint64_t i = 0; i < CAPACITY; i++)
        table[i] = new NgramTree();
}

uint64_t HashTable::hash(const char *str) const
{
    uint64_t hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % CAPACITY;
}

void HashTable::add(string &val)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    uint64_t key = hash(prefix.c_str());
    table[key]->add(prefix, suffix);
}

void HashTable::remove(string &val)
{
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < val.length() && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    uint64_t key = hash(prefix.c_str());
    table[key]->remove(prefix, suffix);
}

const SuffixList *HashTable::suffixesOf(string &prefix) const
{
    uint64_t key = hash(prefix.c_str());

    Node *current = table[key]->root;
    while (current) {
        if (current->prefix == prefix)
            return &current->suffixes;
        if (current->prefix > prefix)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

string HashTable::searchInText(string &text)
{
    string currWord = "";
    string result = "";
    const SuffixList *suffixes;
    set<const string *> foundStrings;
    size_t i = 0;

    while (i <= text.length()) {
        if (text[i] == ' ' || i == text.length()) {
            suffixes = this->suffixesOf(currWord);
            if (suffixes) {
                SuffixNode *suffix = suffixes->getHead();
                while (suffix) {
                    if (foundStrings.find(&(suffix->str)) != foundStrings.end()) {
                        suffix = suffix->next;
                        continue;
                    }
                    bool flag = true;
                    size_t j;
                    for (j = 0; j < suffix->str.length(); j++) {
                        if (text[i + j] != suffix->str[j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (text[i + j] != ' ' && (i + j) != text.length())
                        flag = false;
                    if (flag) {
                        foundStrings.insert(&(suffix->str));
                        result += currWord + (suffix->str) + "|";
                    }
                    suffix = suffix->next;
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

