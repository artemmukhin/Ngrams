#include <iostream>
#include <sstream>
#include <cstdio>
#include "NgramTree.h"

#define NUM_THREADS 4

using namespace std;

int main()
{
    NgramTree ngrams;

    string query = "";
    getline(cin, query);
    while (query != "S") {
        ngrams.add(query);
        getline(cin, query);
    }
    puts("R\n");

    query = "";
    std::stringstream buffer;

    while (std::getline(std::cin, query)) {
        if (query == "F") {
            puts(buffer.str().c_str());
            fflush(stdout);
            buffer.str(std::string());
            buffer.clear();
            continue;
        }
        string prefix;
        string suffix;
        size_t j;
        switch (query[0]) {
            case 'Q':
                query.erase(0, 2);
                buffer << ngrams.searchInText(query) << endl << std::flush;
                break;

            case 'A':
                query.erase(0, 2);
                ngrams.add(query);
                break;

            case 'D':
                query.erase(0, 2);
                prefix = "";
                suffix = "";
                for (j = 0; j < query.length() && query[j] != ' '; j++);
                prefix = query.substr(0, j);
                suffix = query.substr(j, query.length());
                ngrams.remove(prefix, suffix);
                break;
            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }

        //cout << endl;
        //ngrams.print();
        //cout << endl;
    }

    return 0;
}
