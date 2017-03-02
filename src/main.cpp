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
        solver.add((new string(query))->c_str(), query.length());
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

        string *query_buf = new string(query);

        switch (query[0]) {
            case 'Q':
                solver.process(&query_buf->c_str()[2], query.length() - 2, num++);
                break;

            case 'A':
                solver.add(&query_buf->c_str()[2], query.length() - 2);
                break;

            case 'D':
                solver.remove(&query_buf->c_str()[2], query.length() - 2);
                break;
            default:
                std::cerr << "Error unrecognized line: \"" << query << "\"" << std::endl;
                return 1;
        }
    }

    return 0;
}
