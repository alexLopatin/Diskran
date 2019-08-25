#include <string>
#include <fstream>
using namespace std;

ifstream inFile;
ofstream outFile;

void Search(string s, string t) {
    string m = s + '#' + t;
    int n = (int) m.length();
    int z[n] = {};
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && m[z[i]] == m[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
        if(z[i] == s.length()) {
            outFile << i - (int) s.length() - 1<< endl;
        }
    }
}

int main(int argc, char *argv[]) {
    inFile.open(argv[1]);
    string s, t;
    inFile >> s >> t;
    outFile.open(argv[2]);
    Search(s, t);
}