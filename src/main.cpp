#include <iostream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int main()
{
    HashEngine::POWERS[0] = 1;
    for (uint64_t i = 0; i < HashEngine::MAX_LEN; i++)
        HashEngine::POWERS[i + 1] = HashEngine::POWERS[i] * HashEngine::P;

    HashTable ngrams;

    string query = "";
    getline(cin, query);
    while (query != "S") {
        ngrams.add((new string(query))->c_str(), query.length());
        getline(cin, query);
    }
    puts("R");

    query = "";

    while (std::getline(std::cin, query)) {
        if (query == "F") {
            fflush(stdout);
            continue;
        }
        string *query_buf = new string(query);

        switch (query[0]) {
            case 'Q':
                puts((ngrams.searchInText(&query_buf->c_str()[2], query.length() - 2))->c_str());
                break;

            case 'A':
                ngrams.add(&query_buf->c_str()[2], query.length() - 2);
                break;

            case 'D':
                ngrams.remove(&query_buf->c_str()[2], query.length() - 2);
                break;

            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
