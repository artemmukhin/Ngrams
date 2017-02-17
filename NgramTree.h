#include <list>
#include <map>
#include <vector>

using namespace std;

class NgramTree {
private:
    map<string, vector<string> > ngrams;

public:
    void add(string val);

    void remove(string val);

    void searchInText(string text, std::vector<string> &found);
};
