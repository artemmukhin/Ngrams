#include "HashTable.h"

HashTable::HashTable()
{
    table = new NgramTree *[CAPACITY];
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
    size_t i = 0;
    FoundSet foundSuffixes(1000);

    while (i <= text.length()) {
        if (text[i] == ' ' || i == text.length()) {
            suffixes = this->suffixesOf(currWord);
            if (suffixes) {
                SuffixNode *suffix = suffixes->getHead();
                while (suffix) {
                    if (suffix->isFound) {
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
                        suffix->isFound = true;
                        foundSuffixes.add(suffix);
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

    uint32_t s = 0;
    while (s < foundSuffixes.current) {
        foundSuffixes.set[s]->isFound = false;
        s++;
    }

    if (result != "")
        result.pop_back();
    else
        result = "-1";
    return result;
}

FoundSet::FoundSet(uint32_t capacity)
    : capacity(capacity),
      current(0)
{
    set = new SuffixNode *[capacity];
}

void FoundSet::add(SuffixNode *ptr)
{
    if (current < capacity)
        set[current] = ptr;
    else {
        SuffixNode **newSet = (SuffixNode **) realloc(set, 2 * capacity * sizeof(SuffixNode *));
        set = newSet;
        capacity *= 2;
    }
    current++;
}