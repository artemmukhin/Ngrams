#include <string>

using namespace std;

struct SuffixNode
{
    string str;
    SuffixNode *next;
};

class SuffixList
{
private:
    SuffixNode *head;
public:
    SuffixList();
    SuffixList(string &newSuffix);
    SuffixNode *getHead() const;
    void insert(SuffixNode *node, string &newSuffix);
    void remove(string &suffix);
};
