#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include "TLongNumber.h"
using namespace std;

int main(int argc, char *argv[]) {
    mt19937 gen(time(0));
    uniform_int_distribution<int> uid(1,10000000);
    int delA = uid(gen);
    uid = uniform_int_distribution<int>(1,10000);
    int delB = uid(gen);
    if(delA < delB) {
        int tmp = delA;
        delA = delB;
        delB = tmp;
    }
    //delA = 517572;
    //delB = 9097;
    cout << delA << "/";
    
    int res = delA/delB;
    cout << delB << "=" << res <<endl;
    TLongNumber a(to_string(delA));
    TLongNumber b(to_string(delB));
    //TLongNumber a("517572");
    //TLongNumber b("9097");
    cout << a << endl;
    cout << b << endl;
    TLongNumber div = a / b; 
    cout << "result: " << div << endl;
    
    TLongNumber c(to_string(delA/delB));
	ifstream inFile(argv[1]);
    //TLongNumber a;
    //TLongNumber b;
    //inFile >> a >> b;
    inFile.close();

    //cout << a << endl;
    //cout << b << endl;
    //cout << (a / b) << endl;
    //a = TLongNumber("00100001000101010100");
    //cout << a << endl;
    cout << (div == c) << endl;
    ofstream outFile(argv[2]); 
    outFile.close();
}

