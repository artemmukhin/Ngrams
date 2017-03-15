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

    void add(const char *str, uint64_t length, uint64_t num);

    void remove(const char *str, uint64_t length, uint64_t num);

    //void clear();//TODO clear func

    const SuffixList *suffixesOf(const HString prefix) const;
};

class FoundSet
{

    struct FoundNode
    {
        SuffixNode *node;
        const char *prefix;
    };

private:
    uint64_t capacity;

public:
    FoundNode *set;
    uint64_t current;

    FoundSet(uint64_t capacity);

    void add(SuffixNode *ptr, const char *prefix);
};