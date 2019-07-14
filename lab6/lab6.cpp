#include <iostream>
#include <fstream>
#include "TLongNumber.h"
using namespace std;

int main(int argc, char *argv[]) {
    TLongNumber a;
    TLongNumber b;
    TLongNumber c;
	ifstream inFile(argv[1]);
    inFile >> a >> b;
    inFile.close();
    cout << a << endl;
    cout << c << endl;
    cout << (a == c) << endl;
    ofstream outFile(argv[2]); 
    outFile.close();
}