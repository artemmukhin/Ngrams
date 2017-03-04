#pragma once

#include <cstdint>

extern const uint64_t MAX_LEN;
extern const uint64_t P;

extern uint64_t *POWERS;


struct HString
{
    const char *str;
    uint64_t length;
    uint64_t hash;
};

uint64_t hashOfString(const char *str, uint64_t length)
{
    uint64_t *hashes = new uint64_t[MAX_LEN + 1];

    hashes[0] = 0;
    for (uint64_t i = 0; i < length; i++)
        hashes[i + 1] = hashes[i] * P + str[i];

    return hashes[length - 1];
}

void hashesOfPrefixes(const char *str, uint64_t length, uint64_t *hashes)
{
    hashes = new uint64_t[MAX_LEN + 1];

    hashes[0] = 0;
    for (uint64_t i = 0; i < length; i++)
        hashes[i + 1] = hashes[i] * P + str[i];
}
