#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class TStringIterator {         //  итератор, используется для прохода по строке, при каждой итерации выводит слово                   
private:
    string origin;
    string current;
    int currIndex = 0;
    int beginIndex = 0;
    bool IsWord() {
        return ((origin[currIndex]>=97) && (origin[currIndex]<=122))
                    || (origin[currIndex] == '?');
    }
public:
    bool End() {
        return currIndex == origin.size();
    }
    string Next() {
        while(!IsWord()) {
            currIndex++;
            if(End()) {
                break;
            }
        }
        if(origin[currIndex] != ' ') {
            beginIndex = currIndex;
            while(IsWord()) {
                currIndex++;
                if(End()) {
                    break;
                }
            }
        }
        return origin.substr(beginIndex, currIndex - beginIndex);
    }
    TStringIterator(const string& s) {
        origin = s;
    }
};

class TBohr {
private:
    struct TBohrVertex {
        map<string, int> nextVertex;
        int suffLink;
        int suffFLink;
        map<string, int> autoMove;
        int par;
        bool flag;
        string symb;
        int patternNumber;
        TBohrVertex(int p, string s) {
            flag = false;
            suffLink = -1;
            suffFLink = -1;
            par = p;
            symb = s;
        }
    };
    vector<TBohrVertex> Bohr;
    string Pattern;
    vector<string> PatternSplit;
    vector<pair<string, int>> Positions;
    int GetSuffLink(int v);
    int GetAutoMove(int v, string s);
    int GetSuffFLink(int v);
    void Check(int v,int i);
    void AddString(const string& s);
    int PatternLength(int index);
    bool CheckPosition(int positionIndex, int patternIndex);
    vector<int> jokerCount;      // количество джокеров между двумя подобразцами
public:
    TBohr(const string& s);
    void FindAllPos(const string& s);
};