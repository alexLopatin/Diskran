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
    TLongNumber a;
    TLongNumber b;
    string s;
    while(cin >> s) {
        if(IsNumber(s)) {
            a = b;
            b = TLongNumber(s);
        }
        else {
            switch(s[0]) {
                case '+':
                    cout << a + b << endl;
                    break;
                case '-':
                    if( a < b) {
                        cout << "Error" << endl;
                    } 
                    else {
                        cout << a - b << endl;
                    }
                    break;
                case '*':
                    cout << a * b << endl;
                    break;
                case '/':
                    if( b == TLongNumber("0")) {
                        cout << "Error" << endl;
                    }
                    else {
                        cout << a / b << endl;
                    }
                    break;
                case '^':
                    if( a == TLongNumber("0") && b == TLongNumber("0")) {
                        cout << "Error" << endl;
                    }
                    else {
                        cout << a.Pow(b) << endl;
                    }
                    break;
                case '>':
                    cout << BoolToStr(a > b) << endl;
                    break;
                case '<':
                    cout << BoolToStr(a < b) << endl;
                    break;
                case '=':
                    cout << BoolToStr(a == b) << endl;
                    break;
                default:
                    cout << "Error" << endl;
                    break;
            }
        }
    }
}