#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

const unsigned char NUMBER_OF_DIGITS = 6;
const unsigned char MAX_DIGIT_VALUE = 91;
const unsigned char ARGUMENT_COUNT = 3;

struct TCarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];       // Автомобильные номера в формате A 999 BC
};

struct TKeyValuePair {
    TCarNumber Key;
    string Value;                                  //Числа от 0 до 2^64 - 1.
    TKeyValuePair(TCarNumber key, string value);
    TKeyValuePair();
};
void RadixSort(TKeyValuePair pairs[], size_t size);