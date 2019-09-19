#include"TLongNumber.h"
using namespace std;
TLongNumber::TLongNumber(string number) {
    while (number.length() > 1) {
        if (number[0] == '0') {
            number = number.substr(1, number.length() - 1);
        }
        else {
            break;
        }
    }
    for (int i = number.length(); i>0; i -= 9)
        if (i < 9) {
            Num.push_back(atoi(number.substr(0, i).c_str()));
        }
        else {
            Num.push_back(atoi(number.substr(i - 9, 9).c_str()));
        }
}
string TLongNumber::ToString(int number) const {
    string res;
    for (int i = 0; i < 9; i++) {
        int r = number % 10;
        res.insert(0, to_string(r));
        number /= 10;
    }
    return res;
}
TLongNumber::TLongNumber() {

}
bool TLongNumber::IsZero()const {
    return (Num.size() == 0) || (Num[0] == 0);
}

string TLongNumber::GetString() const {
    string str;
    if (Num.size() == 0) {
        str += "0";
    }
    else {
        str += to_string(Num[Num.size() - 1]);
        for (int i = Num.size() - 2; i >= 0; --i) {
            str += ToString(Num[i]);
        }
    }
    return str;
}

std::ostream & operator << (std::ostream &out, const TLongNumber & obj) {
    out << obj.GetString();
    return out;
}
std::istream& operator >> (std::istream& in, TLongNumber& obj) {
    string s;
    in >> s;
    for (int i = s.length(); i>0; i -= 9) {
        if (i < 9) {
            obj.Num.push_back(atoi(s.substr(0, i).c_str()));
        }
        else {
            obj.Num.push_back(atoi(s.substr(i - 9, 9).c_str()));
        }
    }
        return in;
}
TLongNumber operator+ (const TLongNumber &a, const TLongNumber &b)
{
    TLongNumber result;
    int carry = 0;
    for (size_t i = 0; i < ((a.Num.size() > b.Num.size()) ? a.Num.size() : b.Num.size()) || carry; i++) {
        result.Num.push_back(carry
            + (i < a.Num.size() ? a.Num[i] : 0)
            + (i < b.Num.size() ? b.Num[i] : 0));
        carry = result.Num[i] >= BASE;
        if (carry) {
            result.Num[i] -= BASE;
        }
    }
    return result;
}
TLongNumber operator- (const TLongNumber &a, const TLongNumber &b)
{
    TLongNumber result;
    int carry = 0;
    for (size_t i = 0; i < a.Num.size() || carry; i++) {
        result.Num.push_back(-carry
            + a.Num[i]
            - (i < b.Num.size() ? b.Num[i] : 0));
        carry = result.Num[i] < 0;
        if (carry) {
            result.Num[i] += BASE;
        }
    }
    while (result.Num.size() > 1 && result.Num.back() == 0) {
        result.Num.pop_back();
    }
    return result;
}
bool operator> (const TLongNumber &a, const TLongNumber &b)
{
    if (a.IsZero() && b.IsZero()) {
        return false;
    }
    if (a.Num.size() > b.Num.size()) {
        return true;
    }
    if (a.Num.size() < b.Num.size()) {
        return false;
    }
    for (int i = a.Num.size() - 1; i >= 0; --i) {
        if (a.Num[i] > b.Num[i]) {
            return true;
        }
        if (a.Num[i] < b.Num[i]) {
            return false;
        }
    }
    return false;
}
bool operator< (const TLongNumber &a, const TLongNumber &b)
{
    if (a.IsZero() && b.IsZero()) {
        return false;
    }
    if (a.Num.size() < b.Num.size()) {
        return true;
    }
    if (a.Num.size() > b.Num.size()) {
        return false;
    }
    for (int i = a.Num.size() - 1; i >= 0; --i) {
        if (a.Num[i] < b.Num[i]) {

            return true;
        }
        if (a.Num[i] > b.Num[i]) {
            return false;
        }
    }
    return false;
}
bool operator== (const TLongNumber &a, const TLongNumber &b)
{
    return !(a > b) && !(a < b);
}
bool operator<= (const TLongNumber &a, const TLongNumber &b)
{
    return (a < b) || (a == b);
}
bool operator>= (const TLongNumber &a, const TLongNumber &b)
{
    return (a > b) || (a == b);
}
TLongNumber operator* (const TLongNumber &a, const TLongNumber &b)
{
    TLongNumber result;
    result.Num.assign(a.Num.size() + b.Num.size(), 0);
    for (size_t i = 0; i<a.Num.size(); ++i) {
        for (int j = 0, carry = 0; j<(int)b.Num.size() || carry; ++j) {
            long long cur = result.Num[i + j] + a.Num[i] * 1ll * (j < (int)b.Num.size() ? b.Num[j] : 0) + carry;
            result.Num[i + j] = int(cur % BASE);
            carry = int(cur / BASE);
        }
    }
    while (result.Num.size() > 1 && result.Num.back() == 0) {
        result.Num.pop_back();
    }
    return result;
}
int TLongNumber::GetNumberCount() const {
    return GetString().length();
}
TLongNumber operator/ (const TLongNumber &d, const TLongNumber &b)
{
    string result;
    TLongNumber a(d);
    int countB = b.GetNumberCount();
    string strA = a.GetString();
    int carry = 0;
    int countSubA = 0;
    int addedDigits = 0;
    TLongNumber subA;
    while (true) {
        if (countB + carry <= strA.length()) {
            subA = strA.substr(0, countB + carry);
        }
        if (subA < b) {
            if (countB + carry >= strA.length()) {
                break;
            }
            carry++;
            continue;
        }
        for (int i = 1; i <= 10; i++) {
            TLongNumber c = TLongNumber(to_string(i));
            if (c * b > subA) {
                c = b * TLongNumber(to_string(i - 1));
                subA = subA - c;
                for (int i = 0; i < countB + carry - countSubA - 1; i++) {
                    result += "0";
                }
                result += to_string(i - 1);
                countSubA = (int)subA.GetString().length();
                break;
            }
        }
        addedDigits = strA.length() - (countB + carry);
        strA = subA.GetString() + strA.substr(countB + carry, addedDigits);
        a = TLongNumber(strA);
        carry = 0;
    }
    for (int i = 0; i < addedDigits; i++) {
        result += "0";
    }
    return TLongNumber(result);
}
int TLongNumber::Mod2() {
    return Num.back() % 2;
}
TLongNumber TLongNumber::Pow(TLongNumber power) {
    TLongNumber a(*this);
    TLongNumber res("1");
    TLongNumber zero = TLongNumber("0");
    TLongNumber one = TLongNumber("1");
    TLongNumber two = TLongNumber("2");
    while (power > zero) {
        if (power.Mod2() == 1) {
            res = res * a;
            power = power - one;
        }
        else {
            a = a * a;
            power = power / two;
        }
    }
    return res;
}