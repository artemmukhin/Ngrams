#pragma once

#include "NgramTree.h"
#include <cstdint>
#define CAPACITY 10267

class HashTable
{
private:
    NgramTree **table;

    uint64_t hash(const char *str, uint64_t length) const;

public:
    HashTable();

    void add(const char *str, uint64_t length);

    void remove(const char *str, uint64_t length);

    const SuffixList *suffixesOf(const HString prefix) const;

    string *searchInText(const char *str, uint64_t length);
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