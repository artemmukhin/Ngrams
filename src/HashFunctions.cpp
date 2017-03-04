#include "HashFunctions.h"

const uint64_t MAX_LEN = 10000;
const uint64_t P = 239017;
uint64_t *POWERS = new uint64_t[MAX_LEN + 1];