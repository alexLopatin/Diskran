#include <iostream>
#include <fstream>
#include "TLongNumber.h"
using namespace std;

int main(int argc, char *argv[]) {
    TLongNumber a;
    TLongNumber b;
	ifstream inFile(argv[1]);
    inFile >> a >> b;
    inFile.close();

    //cout << a << endl;
    //cout << b << endl;
    cout << a / b << endl;
    ofstream outFile(argv[2]); 
    outFile.close();
}

