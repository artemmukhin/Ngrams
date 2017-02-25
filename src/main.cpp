#include <iostream>
#include <sstream>
#include "HashTable.h"

using namespace std;

int main()
{
    HashTable ngrams;

    string query = "";
    getline(cin, query);
    while (query != "S") {
        ngrams.add(query);
        getline(cin, query);
    }
    puts("R");

    query = "";

    while (std::getline(std::cin, query)) {
        if (query == "F") {
            fflush(stdout);
            continue;
        }
        switch (query[0]) {
            case 'Q':
                query.erase(0, 2);
                puts(ngrams.searchInText(query).c_str());
                break;

            case 'A':
                query.erase(0, 2);
                ngrams.add(query);
                break;

            case 'D':
                query.erase(0, 2);
                ngrams.remove(query);
                break;
            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
