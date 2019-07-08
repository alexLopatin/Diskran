#include <cstring>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const unsigned char ALPHABET_SIZE = 26;

struct  TBohrVertex {
    int nextVertex[ALPHABET_SIZE];
    int suffLink;
    int suffFLink;
    int autoMove[ALPHABET_SIZE];
    int par;
    bool flag;
    char symb;
    int patternNumber;
    TBohrVertex(int p, char c) {
        memset(nextVertex, 255, sizeof(nextVertex));
        memset(autoMove, 255, sizeof(autoMove));
        flag = false;
        suffLink = -1;
        suffFLink = -1;
        par = p;
        symb = c;
    }
};

class TBohr {
private:
    vector<TBohrVertex> Bohr;
    string Pattern;
    vector<string> PatternSplit;
    int GetSuffLink(int v);
    int GetAutoMove(int v, char ch);
    int GetSuffFLink(int v);
    void Check(int v,int i);
    void AddString(const string& s);
public:
    TBohr(const string& s);
    bool IsStringInBohr(const string& s);
    void FindAllPos(const string& s);
};