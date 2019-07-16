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
    string GetString() const{
        string str;
        if(Num.size() == 0) {
            str += "0";
        }
        else {
            str += to_string(Num[Num.size() - 1]);
            for ( int i = Num.size() - 2; i >= 0; --i) {
                str += ToString(Num[i]);
            }
        }
        return str;
    }
    friend std::ostream & operator << (std::ostream &out, const TLongNumber & obj) {
        out << obj.GetString();
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
    friend bool operator<= (const TLongNumber &a, const TLongNumber &b) 
    {
        return (a < b) || (a == b);
    }
    friend bool operator>= (const TLongNumber &a, const TLongNumber &b) 
    {
        return (a > b) || (a == b);
    }
    friend TLongNumber operator* (const TLongNumber &a, const TLongNumber &b) 
    {
        TLongNumber result;
        result.Num.assign(a.Num.size() + b.Num.size(), 0);
        for (size_t i=0; i<a.Num.size(); ++i){
            for (int j=0, carry=0; j<(int)b.Num.size() || carry; ++j) {
                long long cur = result.Num[i+j] + a.Num[i] * 1ll * (j < (int)b.Num.size() ? b.Num[j] : 0) + carry;
                result.Num[i+j] = int (cur % BASE);
                carry = int (cur / BASE);
            }
        }
        while (result.Num.size() > 1 && result.Num.back() == 0) {
            result.Num.pop_back();
        }
        return result;
    }
    int GetNumberCount() const {
        return GetString().length();
    }
    TLongNumber SubNumber(int start, int count) const {
        string subNum = GetString();
        return TLongNumber(subNum.substr(start, count));
    }
    friend TLongNumber operator/ (const TLongNumber &d, const TLongNumber &b) 
    {
        string result;
        TLongNumber a(d);
        int countB = b.GetNumberCount();
        string strA = a.GetString();
        int carry = 0;
        int j = 0;
        while(true) {
            j++;
            TLongNumber subA = strA.substr(0, countB + carry);
            cout << strA.substr(0, countB + carry) << endl;
            if(subA < b) {
                if(carry > 0) {
                    result += "0";
                }
                if(countB + carry >= strA.length()) {
                    break;
                }
                carry++;
                continue;
            }

            TLongNumber c;
            for( int i = 2; i <= 10; i++) {
                c = TLongNumber(to_string(i));
                if(c * b > subA) {
                    c = b * TLongNumber(to_string(i - 1));
                    result += to_string(i - 1);
                    break;
                }
            }
            subA = subA - c;
            for (int i = 0; i < countB - subA.GetString().length(); i++) {
                result += "0";
            }
            strA = subA.GetString() + strA.substr(countB + carry, strA.length());
            a = TLongNumber(strA);
            carry = 0;
        }
        cout << "result: " << result << endl;
        return TLongNumber(result);
    }
    TLongNumber Pow(TLongNumber power) {
        return power;
    }
};