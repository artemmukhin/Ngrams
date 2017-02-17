#include <iostream>

#include "NgramTree.h"

using namespace std;

int main()
{

    NgramTree ngrams;

    string query = "";
    getline(cin, query);
    do {
        ngrams.add(query);
        getline(cin, query);
    } while (query != "S");

    cout << "R" << endl;
    //ngrams.print();
    //cout << endl;

    query = "";
    getline(cin, query);
    do {
        switch (query[0]) {
            case 'Q': {
                query.erase(0, 2);
                vector <string> result;
                ngrams.searchInText(query, result);
                for (int it = 0; it < result.size(); it++)
                    cout << result[it] << ((it + 1 == result.size()) ? "\n" : "|");


                break;
            }
            case 'A':
                query.erase(0, 2);
                ngrams.add(query);
                break;

            case 'D':
                query.erase(0, 2);
                ngrams.remove(query);
                break;
        }

        getline(cin, query);
    } while (query != "F");

    return 0;
}
