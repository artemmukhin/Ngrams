#include <iostream>
#include <sstream>

#include "Solver.h"

using namespace std;

int main()
{
    HashEngine::POWERS[0] = 1;
    for (uint64_t i = 0; i < HashEngine::MAX_LEN; i++)
        HashEngine::POWERS[i + 1] = HashEngine::POWERS[i] * HashEngine::P;

    Solver solver;

    string query = "";
    std::getline(std::cin, query);
    while (query != "S") {
        solver.add((new string(query))->c_str(), query.length(), 0);
        getline(cin, query);
    }
    solver.waitForInit();
    //solver.flush();

    puts("R");

    query = "";

    int num = 0;
    while (std::getline(std::cin, query)) {
        if (query == "F") {
            solver.flush();
            continue;
        }

        string *query_buf = new string(query);
        num++;

        switch (query[0]) {
            case 'Q':
                solver.solve(&query_buf->c_str()[2], query.length() - 2, num);
                break;

            case 'A':
                solver.add(&query_buf->c_str()[2], query.length() - 2, num);
                break;

            case 'D':
                solver.remove(&query_buf->c_str()[2], query.length() - 2, num);
                break;

            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
