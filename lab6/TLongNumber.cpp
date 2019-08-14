#include"TLongNumber.h"
using namespace std;
TLongNumber::TLongNumber(string number) {
    while(number.length() > 1) {
        if(number[0] == '0') {
            number = number.substr(1, number.length() - 1);
        }
        else {
            break;
        }
    }
    for (int i = number.length(); i>0; i-=9)
    if (i < 9) {
        Num.push_back (atoi (number.substr (0, i).c_str()));
    }
    else {
        Num.push_back (atoi (number.substr (i-9, 9).c_str()));
    }
}
string TLongNumber::ToString(int number) const{
    string res;
    for ( int i = 0; i < 9; i++) {
        int r = number % 10;
        res.insert(0,to_string(r));
        number /= 10; 
    }
    return res;
}
TLongNumber::TLongNumber() {

}
bool TLongNumber::IsZero()const {
    return (Num.size() == 0) || (Num[0] == 0);
}