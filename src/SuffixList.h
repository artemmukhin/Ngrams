#include <string>

using namespace std;

struct SuffixNode
{
    string str;
    uint64_t hash;
    SuffixNode *next;
    bool isFound = false; // only for search
};

class SuffixList
{
private:
    SuffixNode *head;
    uint64_t hash(string &s);
public:
    SuffixList();
    SuffixList(string &newSuffix);
    SuffixNode *getHead() const;
    void insert(SuffixNode *node, string &newSuffix);
    void remove(string &suffix);
};
