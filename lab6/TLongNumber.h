#include <iostream>
#include <vector>
using namespace std;
const int BASE = 1000 * 1000 * 1000;

struct TLongNumber {
    vector<int> Num;
    TLongNumber(string number);
    string ToString(int number) const;
    TLongNumber();
    bool IsZero()const;
    friend std::ostream & operator << (std::ostream &out, const TLongNumber & obj) {
        if(obj.Num.size() == 0) {
            out << 0;
        }
        else {
            out << to_string(obj.Num[obj.Num.size() - 1]);
            for ( int i = obj.Num.size() - 2; i >= 0; --i) {
                out << obj.ToString(obj.Num[i]);
            }
        }
        return out;
    }
    friend std::istream& operator >> (std::istream& in, TLongNumber& obj) {
        string s;
        in >> s;
        for (int i = s.length(); i>0; i-=9)
        if (i < 9) {
            obj.Num.push_back (atoi (s.substr (0, i).c_str()));
        }
        else {
            obj.Num.push_back (atoi (s.substr (i-9, 9).c_str()));
        }
        return in;
    }
    friend TLongNumber operator+ (const TLongNumber &a, const TLongNumber &b) 
    {
        TLongNumber result;
        int carry = 0;
        for ( size_t i = 0; i < max(a.Num.size(), b.Num.size()) || carry; i++) {
            result.Num.push_back(carry 
                + (i < a.Num.size() ? a.Num[i] : 0) 
                + (i < b.Num.size() ? b.Num[i] : 0));
            carry = result.Num[i] >= BASE;
            if(carry) {
                result.Num[i] -= BASE;
            }
        }
        return result;
    }
    friend TLongNumber operator- (const TLongNumber &a, const TLongNumber &b) 
    {
        TLongNumber result;
        int carry = 0;
        for ( size_t i = 0; i < a.Num.size() || carry; i++) {
            result.Num.push_back(-carry 
                + a.Num[i]
                - (i < b.Num.size() ? b.Num[i] : 0));
            carry = result.Num[i] < 0;
            if(carry) {
                result.Num[i] += BASE;
            }
        }
        while (result.Num.size() > 1 && result.Num.back() == 0) {
            result.Num.pop_back();
        }
        return result;
    }
    friend bool operator> (const TLongNumber &a, const TLongNumber &b) 
    {
        if(a.IsZero() && b.IsZero()) {
            return false;
        }
        if(a.Num.size() > b.Num.size()){
            return true;
        }
        if(a.Num.size() < b.Num.size()){
            return false;
        }
        for ( int i = a.Num.size() - 1; i >= 0; --i) {
            if(a.Num[i] > b.Num[i]){
                return true;
            }
            if(a.Num[i] < b.Num[i]){
                return false;
            }
        }
        return false;
    }
    friend bool operator< (const TLongNumber &a, const TLongNumber &b) 
    {
        if(a.IsZero() && b.IsZero()) {
            return false;
        }
        if(a.Num.size() < b.Num.size()){
            return true;
        }
        if(a.Num.size() > b.Num.size()){
            return false;
        }
        for ( int i = a.Num.size() - 1; i >= 0; --i) {
            cout << a.Num[i] << ' ' << b.Num[i] << endl;
            if(a.Num[i] < b.Num[i]){

                return true;
            }
            if(a.Num[i] > b.Num[i]){
                return false;
            }
        }
        return false;
    }
    friend bool operator== (const TLongNumber &a, const TLongNumber &b) 
    {
        return !(a > b) && !(a < b);
    }

};