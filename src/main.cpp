#include <iostream>
#include <pthread.h>
#include <sstream>

#include "Solver.h"

using namespace std;

int main()
{
    Solver solver;

    string query = "";
    getline(cin, query);
    while (query != "S") {
        solver.add(query, 0);
        getline(cin, query);
    }

    solver.rebuild();

    cout << "R" << endl;

    string texts[NUM_THREADS];
    int text_num[NUM_THREADS];
    int text_count = 0;

    int num = 0;
    while (std::getline(std::cin, query)) {
        num++;
        if (query == "F") {
            solver.solve(texts, text_num, text_count);
            std::cout.flush();
            continue;
        }
        string prefix;
        string suffix;

        switch (query[0]) {
            case 'Q':
                query.erase(0, 2);
                texts[text_count] = query;
                text_num[text_count] = num;
                text_count++;

                if(text_count == NUM_THREADS){
                    solver.solve(texts, text_num, text_count);
                    text_count = 0;
                }

                break;

            case 'A':
                query.erase(0, 2);
                solver.add(query, num);
                break;

            case 'D':
                query.erase(0, 2);
                solver.remove(query, num);
                break;
            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
