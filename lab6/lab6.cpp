#include <iostream>
#include <fstream>
#include "TLongNumber.h"
using namespace std;

bool IsNumber(string s) {
    return ((s[0] > 47) && (s[0] < 58));
}

string BoolToStr(bool val) {
    return (val ? "true" : "false");
}

int main(int argc, char *argv[]) {
	ifstream inFile(argv[1]);
    ofstream outFile(argv[2]); 
    TLongNumber a;
    TLongNumber b;
    string s;
    while(inFile >> s) {
        if(IsNumber(s)) {
            a = b;
            b = TLongNumber(s);
        }
        else {
            switch(s[0]) {
                case '+':
                    outFile << a + b << endl;
                    break;
                case '-':
                    if( a < b) {
                        outFile << "Error" << endl;
                    } 
                    else {
                        outFile << a - b << endl;
                    }
                    break;
                case '*':
                    outFile << a * b << endl;
                    break;
                case '/':
                    if( b == TLongNumber("0")) {
                        outFile << "Error" << endl;
                    }
                    else {
                        outFile << a / b << endl;
                    }
                    break;
                case '^':
                    if( a == TLongNumber("0") && b == TLongNumber("0")) {
                        outFile << "Error" << endl;
                    }
                    else {
                        outFile << a.Pow(b) << endl;
                    }
                    break;
                case '>':
                    outFile << BoolToStr(a > b) << endl;
                    break;
                case '<':
                    outFile << BoolToStr(a < b) << endl;
                    break;
                case '=':
                    outFile << BoolToStr(a == b) << endl;
                    break;
                default:
                    outFile << "Error" << endl;
                    break;
            }
        }
    }
    inFile.close();
    outFile.close();
}