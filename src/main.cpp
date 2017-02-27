#include <iostream>
#include <sstream>

#include "Solver.h"

using namespace std;

int main()
{

    Solver solver;

    string query = "";
    getline(cin, query);
    while (query != "S") {
        solver.add(query);
        getline(cin, query);
    }

    solver.wait();

    puts("R");

    query = "";
    int num = 0;

    while (std::getline(std::cin, query)) {
        if (query == "F") {
            solver.flush();
            fflush(stdout);
            continue;
        }
        switch (query[0]) {
            case 'Q':
                query.erase(0, 2);
                solver.process(query, num++);
                break;

            case 'A':
                query.erase(0, 2);
                solver.add(query);
                break;

            case 'D':
                query.erase(0, 2);
                solver.remove(query);
                break;
            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
