#pragma once

#include "NgramTree.h"
#include <cstdint>
#define CAPACITY 10267

class HashTable
{
private:
    NgramTree **table;

    uint64_t hash(const char *str) const;

public:
    HashTable();

    void add(const char *str, int length);

    void remove(const char *str, int length);

    const SuffixList *suffixesOf(string &prefix) const;

    string* searchInText(const char *str, int length);
};


class FoundSet
{
private:
    uint32_t capacity;

public:
    SuffixNode **set;
    uint32_t current;

    FoundSet(uint32_t capacity);
    //~FoundSet();

    void add(SuffixNode *ptr);
};