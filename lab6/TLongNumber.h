#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int BASE = 1000 * 1000 * 1000;

struct TLongNumber {
    vector<int> Num;
    TLongNumber(string number);
    TLongNumber(const TLongNumber& number) {
        for (int i = 0; i < number.Num.size(); i++) {
            Num.push_back(number.Num[i]);
        }
    }
    string ToString(int number) const;
    TLongNumber();
    bool IsZero()const;
    string GetString() const;
    int GetNumberCount() const;
    int Mod2();
    friend std::ostream & operator << (std::ostream &out, const TLongNumber & obj);
    friend std::istream& operator >> (std::istream& in, TLongNumber& obj);
    friend TLongNumber operator+ (const TLongNumber &a, const TLongNumber &b);
    friend TLongNumber operator- (const TLongNumber &a, const TLongNumber &b);
    friend bool operator> (const TLongNumber &a, const TLongNumber &b);
    friend bool operator< (const TLongNumber &a, const TLongNumber &b);
    friend bool operator== (const TLongNumber &a, const TLongNumber &b);
    friend bool operator<= (const TLongNumber &a, const TLongNumber &b);
    friend bool operator>= (const TLongNumber &a, const TLongNumber &b);    
    friend TLongNumber operator* (const TLongNumber &a, const TLongNumber &b);
    friend TLongNumber operator/ (const TLongNumber &d, const TLongNumber &b);
    TLongNumber Pow(TLongNumber power);
};
