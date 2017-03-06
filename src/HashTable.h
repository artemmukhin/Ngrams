#pragma once

#include "NgramTree.h"
#include <cstdint>

class HashTable
{
private:
    NgramTree **table;

    uint64_t hash(const char *str, uint64_t length) const;

public:
    static const uint64_t CAPACITY;

    HashTable();

    void add(const char *str, uint64_t length);

    void remove(const char *str, uint64_t length);

    const SuffixList *suffixesOf(const HString prefix) const;

    string *searchInText(const char *str, uint64_t length);
};

class FoundSet
{
private:
    uint64_t capacity;

public:
    SuffixNode **set;
    uint64_t current;

    FoundSet(uint64_t capacity);
    //~FoundSet();

    void add(SuffixNode *ptr);
};