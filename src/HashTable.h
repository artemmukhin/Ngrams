#include "NgramTree.h"
#include <cstdint>
#define CAPACITY 1000000

class HashTable
{
private:
    NgramTree *table[CAPACITY];

    uint64_t hash(const char *str) const;

public:
    HashTable();

    void add(string &val);

    void remove(string &val);

    const SuffixList *suffixesOf(string &prefix) const;

    string searchInText(string &text);
};
