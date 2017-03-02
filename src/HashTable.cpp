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

void HashTable::add(const char *str, int length)
{
    string val(str);
    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < length && val[i] != ' '; i++);
    prefix = val.substr(0, i);
    suffix = val.substr(i, val.length());

    uint64_t key = hash(prefix.c_str());
    table[key]->add(prefix, suffix);
}

void HashTable::remove(const char *str, int length)
{
    string val(str);

    string prefix;
    string suffix;
    size_t i;

    for (i = 0; i < length && val[i] != ' '; i++);
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

string* HashTable::searchInText(const char *str, int length)
{
    const uint64_t MAX_LEN = 1000000;
    const int P = 239017;
    uint64_t *hashes = new uint64_t[MAX_LEN + 1];
    uint64_t *powers = new uint64_t[MAX_LEN + 1];

    powers[0] = 1;
    hashes[0] = 0;
    for (size_t i = 0; i < length; i++) {
        hashes[i + 1] = hashes[i] * P + str[i];
        powers[i + 1] = powers[i] * P;
    }

    string currWord = "";
    string* result = new string();
    const SuffixList *suffixes;
    size_t i = 0;
    FoundSet foundSuffixes(10000);

    while (i <= length){
        if (str[i] == ' ' || i == length) {
            suffixes = this->suffixesOf(currWord);
            if (suffixes) {
                SuffixNode *suffix = suffixes->getHead();
                while (suffix) {
                    uint64_t textHash = hashes[i + suffix->str.size()] - hashes[i] * powers[suffix->str.size()];
                    if (suffix->isFound || suffix->hash != textHash) {
                        suffix = suffix->next;
                        continue;
                    }

                    bool flag = true;
                    size_t j;
                    for (j = 0; j < suffix->str.length(); j++) {
                        if (str[i + j] != suffix->str[j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (str[i + j] != ' ' && (i + j) != length)
                        flag = false;
                    if (flag) {
                        suffix->isFound = true;
                        foundSuffixes.add(suffix);
                        result->append(currWord);
                        result->append(suffix->str);
                        result->append("|");
                    }
                    suffix = suffix->next;
                }
            }
            currWord = "";
            i++;
        }
        currWord += str[i++];
    }

    uint32_t s = 0;
    while (s < foundSuffixes.current) {
        foundSuffixes.set[s]->isFound = false;
        s++;
    }

    if (!result->empty())
        result->pop_back();
    else
        result = new string("-1");

    delete[] hashes;
    delete[] powers;

    return result;
}

FoundSet::FoundSet(uint32_t capacity)
        : capacity(capacity),
          current(0)
{
    set = new SuffixNode *[capacity];
}

/*
FoundSet::~FoundSet()
{
    delete[] set;
}
*/

void FoundSet::add(SuffixNode *ptr)
{
    if (current < capacity)
        set[current] = ptr;
    else {
        SuffixNode **newSet = new SuffixNode *[2 * capacity];
        for (uint32_t i = 0; i < capacity; i++)
            newSet[i] = set[i];
        delete[] set;
        set = newSet;
        capacity *= 2;
    }
    current++;
}