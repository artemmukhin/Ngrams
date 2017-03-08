#pragma once

#include "NgramTree.h"
#include <cstdint>

class HashTable
{
private:
    NgramTree **table;

public:
    static const uint64_t CAPACITY;

    HashTable();

    void add(const char *str, uint64_t length, int num);

    void remove(const char *str, uint64_t length, int num);

    void clear();//TODO clear func

    const SuffixList *suffixesOf(const HString prefix) const;

    string *searchInText(const char *str, uint64_t length);//TODO move to new class
};

class FoundSet
{
private:
    uint64_t capacity;

public:
    SuffixNode **set;
    uint64_t current;

    FoundSet(uint64_t capacity);

    void add(SuffixNode *ptr);
};