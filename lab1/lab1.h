#include <iostream>
#include <cstring>
#include <fstream>

const unsigned char NUMBER_OF_DIGITS = 6;
const unsigned char MAX_DIGIT_VALUE = 91;
const unsigned char ARGUMENT_COUNT = 3;

struct CarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];       // Автомобильные номера в формате A 999 BC
};

struct KeyValuePair {
    CarNumber Key;
    unsigned long long Value;                                  //Числа от 0 до 2^64 - 1.
    KeyValuePair(CarNumber key, unsigned long long value);
    KeyValuePair();
};
void RadixSort(KeyValuePair pairs[], size_t size);