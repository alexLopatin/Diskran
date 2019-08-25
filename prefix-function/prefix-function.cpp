#include <string>
#include <iostream>
#include <fstream>
using namespace std;

ifstream inFile;
ofstream outFile;

void KMP(string s) {
    s = s + '#';
    int n = (int) s.length();
    int pi[n];
    pi[0] = 0;
    char currentChar;
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    int i = 0;
    int j = 0;
    while(inFile.get(currentChar)) {
        if(currentChar == '\n') {
            continue;
        }
        while (j > 0 && currentChar != s[j])
            j = pi[j - 1];
        if (currentChar == s[j])  ++j;
        if ( j == s.length() - 1) {
            outFile << i - n + 2 << endl;
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    inFile.open(argv[1]);
    string s;
    inFile >> s;
    outFile.open(argv[2]);
    KMP(s);
}