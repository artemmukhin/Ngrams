#pragma once

#include <cstdint>
#include <cstring>

struct HString
{
    const char *str;
    uint64_t length;
    uint64_t hash;
};

class HashEngine
{
private:
    static uint64_t *staticHashes;

    HashEngine()
    {}
    ~HashEngine()
    {}
    HashEngine(HashEngine const &) = delete;
    HashEngine &operator=(HashEngine const &) = delete;

public:
    static const uint64_t MAX_LEN;
    static const uint64_t P;
    static uint64_t *POWERS;
    static uint64_t FOUND_SET_SIZE;

    static uint64_t hashOfString(const char *str, uint64_t length)
    {
        staticHashes[0] = 0;
        for (uint64_t i = 0; i < length; i++)
            staticHashes[i + 1] = staticHashes[i] * P + str[i];

        return staticHashes[length];
    }

    // this method is used only for search in text
    static void hashesOfPrefixes(const char *str, uint64_t length, uint64_t *hashes)
    {
        hashes[0] = (uint64_t) *str;
        for (uint64_t i = 0; i < length; i++)
            hashes[i + 1] = hashes[i] * P + str[i];
    }

    static bool isEqual(const HString s1, const HString s2) {
        if (s1.hash != s2.hash)
            return false;
        if (s1.length != s2.length)
            return false;

        return true;
    }
};