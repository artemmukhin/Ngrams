#include "HashTable.h"

HashTable::HashTable()
{
    table = new NgramTree *[CAPACITY];
    for (uint64_t i = 0; i < CAPACITY; i++)
        table[i] = new NgramTree();
}

uint64_t HashTable::hash(const char *str, uint64_t length) const
{
    return hashOfString(str, length) % CAPACITY;
}

void HashTable::add(const char *str, uint64_t length)
{
    const char *prefixStr = str;
    const char *suffixStr;
    uint64_t prefixSize = 0;
    while (*prefixStr++ != ' ' && prefixSize++ != length)
        ;
    suffixStr = prefixStr;
    prefixStr--;

    uint64_t hashPrefix = hashOfString(prefixStr, prefixSize);
    uint64_t hashSuffix = hashOfString(suffixStr, length - prefixSize);
    HString prefix = {prefixStr, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash]->add(prefix, suffix);
}

void HashTable::remove(const char *str, uint64_t length)
{
    const char *prefixStr = str;
    const char *suffixStr;
    uint64_t prefixSize = 0;
    while (*prefixStr++ != ' ' && prefixSize++ != length)
        ;
    suffixStr = prefixStr;
    prefixStr--;

    uint64_t hashPrefix = hashOfString(prefixStr, prefixSize);
    uint64_t hashSuffix = hashOfString(suffixStr, length - prefixSize);
    HString prefix = {prefixStr, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash]->remove(prefix, suffix);
}

const SuffixList *HashTable::suffixesOf(const HString prefix) const
{
    Node *current = table[prefix.hash]->root;
    while (current) {
        if (current->prefix.hash == prefix.hash) {
            if (strcmp(current->prefix.str, prefix.str) == 0)
                return &current->suffixes;
        }

        // можно сравнивать в дереве не по строке, а по хешу...

        if (strcmp(current->prefix.str, prefix.str) > 0)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

string *HashTable::searchInText(const char *str, uint64_t length)
{
    uint64_t *hashes = new uint64_t[MAX_LEN + 1];
    hashesOfPrefixes(str, length, hashes);

    string currWord = "";
    string *result = new string();
    const SuffixList *suffixes;
    size_t i = 0;
    FoundSet foundSuffixes(10000);

    while (i <= length) {
        if (str[i] == ' ' || i == length) {
            suffixes = this->suffixesOf({currWord.c_str(), currWord.length(),
                                         hashOfString(currWord.c_str(), currWord.length())
                                        });
            if (suffixes) {
                SuffixNode *suffixNode = suffixes->getHead();
                while (suffixNode) {
                    uint64_t textHash = hashes[i + suffixNode->suffix.length] -
                                        hashes[i] * POWERS[suffixNode->suffix.length];
                    if (suffixNode->isFound || suffixNode->suffix.hash != textHash) {
                        suffixNode = suffixNode->next;
                        continue;
                    }

                    bool flag = true;
                    size_t j;
                    for (j = 0; j < suffixNode->suffix.length; j++) {
                        if (str[i + j] != suffixNode->suffix.str[j]) {
                            flag = false;
                            break;
                        }
                    }
                    if (str[i + j] != ' ' && (i + j) != length)
                        flag = false;
                    if (flag) {
                        suffixNode->isFound = true;
                        foundSuffixes.add(suffixNode);
                        result->append(currWord);
                        result->append(suffixNode->suffix.str);
                        result->append("|");
                    }
                    suffixNode = suffixNode->next;
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