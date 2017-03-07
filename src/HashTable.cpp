#include "HashTable.h"

const uint64_t HashTable::CAPACITY = 10267;
//const uint64_t HashTable::CAPACITY = 11;

HashTable::HashTable()
{
    table = new NgramTree *[CAPACITY];
    for (uint64_t i = 0; i < CAPACITY; i++)
        table[i] = new NgramTree();
}

void HashTable::add(const char *str, uint64_t length, int num)
{
    const char *suffixStr = str;
    uint64_t prefixSize = 0;
    while ( !(*suffixStr == ' ' || prefixSize == length) ) {
        suffixStr++;
        prefixSize++;
    }

    uint64_t hashPrefix = HashEngine::hashOfString(str, prefixSize);
    uint64_t hashSuffix = HashEngine::hashOfString(suffixStr, length - prefixSize);
    HString prefix = {str, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash % CAPACITY]->add(prefix, suffix, num);
}

void HashTable::remove(const char *str, uint64_t length, int num)
{
    const char *suffixStr = str;
    uint64_t prefixSize = 0;
    while ( !(*suffixStr == ' ' || prefixSize == length) ) {
        suffixStr++;
        prefixSize++;
    }

    uint64_t hashPrefix = HashEngine::hashOfString(str, prefixSize);
    uint64_t hashSuffix = HashEngine::hashOfString(suffixStr, length - prefixSize);
    HString prefix = {str, prefixSize, hashPrefix};
    HString suffix = {suffixStr, length - prefixSize, hashSuffix};

    table[prefix.hash % CAPACITY]->remove(prefix, suffix, num);
}

const SuffixList *HashTable::suffixesOf(const HString prefix) const
{
    Node *current = table[prefix.hash % CAPACITY]->root;
    while (current) {
        if (HashEngine::isEqual(current->prefix, prefix))
            return &current->suffixes;

        if (current->prefix.hash > prefix.hash)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

string *HashTable::searchInText(const char *str, uint64_t length)
{
    uint64_t *hashes = new uint64_t[HashEngine::MAX_LEN + 1];
    HashEngine::hashesOfPrefixes(str, length, hashes);

    string currWord = "";
    string *result = new string();
    const SuffixList *suffixes;
    size_t i = 0;
    FoundSet foundSuffixes(HashEngine::FOUND_SET_SIZE);

    while (i <= length) {
        if (str[i] == ' ' || i == length) {
            suffixes = this->suffixesOf({currWord.c_str(), currWord.length(),
                                         HashEngine::hashOfString(currWord.c_str(), currWord.length())
                                        });

            if (suffixes) {
                SuffixNode *suffixNode = suffixes->getHead();
                while (suffixNode) {
                    uint64_t textHash = hashes[i + suffixNode->suffix.length] -
                        hashes[i] * HashEngine::POWERS[suffixNode->suffix.length];

                    if (!suffixNode->isFound) {
                        HString textSuffix {&(str[i]), suffixNode->suffix.length, textHash};
                        if (HashEngine::isEqual(suffixNode->suffix, textSuffix)) {
                            if (i + suffixNode->suffix.length == length || str[i + suffixNode->suffix.length] == ' ') {
                                suffixNode->isFound = true;
                                foundSuffixes.add(suffixNode);
                                result->append(currWord);
                                result->append(suffixNode->suffix.str);
                                result->append("|");
                            }
                        }
                    }
                    suffixNode = suffixNode->next;
                }
            }
            currWord = "";
            i++;
        }
        currWord += str[i++];
    }

    uint64_t s = 0;
    while (s < foundSuffixes.current) {
        foundSuffixes.set[s]->isFound = false;
        s++;
    }

    if (!result->empty())
        result->pop_back();
    else
        result = new string("-1");

    //delete[] hashes;

    return result;
}

FoundSet::FoundSet(uint64_t capacity)
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
    /*
    else {
        SuffixNode **newSet = new SuffixNode *[2 * capacity];
        for (uint64_t i = 0; i < capacity; i++)
            newSet[i] = set[i];
        delete[] set;
        set = newSet;
        capacity *= 2;
    }
    */
    current++;
}