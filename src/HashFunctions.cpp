#include "HashFunctions.h"

const uint64_t HashEngine::MAX_LEN = 100;
const uint64_t HashEngine::P = 239017;
uint64_t *HashEngine::POWERS = new uint64_t[HashEngine::MAX_LEN + 1];
uint64_t *HashEngine::staticHashes = new uint64_t[MAX_LEN + 1];