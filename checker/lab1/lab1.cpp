#include "lab1.h"
using namespace std;

TKeyValuePair::TKeyValuePair(TCarNumber key, unsigned long long value) {
    Key = key;
    Value = value;
}
TKeyValuePair::TKeyValuePair() {
    
}


void RadixSort(TKeyValuePair pairs[], size_t size, int l, int r, int d) {
    if(d >= 6 || l >= r) {
        return;
    }
    unsigned long long countArray[MAX_DIGIT_VALUE + 1];
    for (int j = 0; j < MAX_DIGIT_VALUE + 1; ++j) {
        countArray[j] = 0;
    }
    TKeyValuePair *c = new TKeyValuePair[size];
    for ( int i = l; i <= r; i++) {
        int j = pairs[i].Key.vals[d];
        countArray[j + 1] ++;
    }
    for (int j = 2; j <=  MAX_DIGIT_VALUE; j++) {
        countArray[j] += countArray[j - 1];
    }
    for ( int i = l; i <= r; i++) {
        int j = pairs[i].Key.vals[d];
        c[l + countArray[j]] = pairs[i];
        countArray[j]--;
    }
    for ( int i = l; i <= r; i++) {
        pairs[i] = c[i];
    }
    delete [] c;
    RadixSort(pairs, size, l, l + countArray[0] - 1, d + 1);
    for ( int i = 1; i <= MAX_DIGIT_VALUE; i++) {
        RadixSort(pairs, size, l + countArray[i - 1], l + countArray[i] - 1, d + 1);
    }
}

int main(int argc, char *argv[]) {
        size_t size = 0;
        size_t currSize = 1;
        TKeyValuePair* pairs = new TKeyValuePair[currSize];
        char val0;
        while (cin >> val0) {
            if(currSize==size) {
                TKeyValuePair* temp = new TKeyValuePair[2 * currSize];
                copy(pairs, pairs + currSize, temp);
                currSize *= 2;
                delete [] pairs;
                pairs = temp;
            }

            unsigned char vals[NUMBER_OF_DIGITS];

            unsigned long long value = 0;
            vals[0] = val0;
            cin >> vals[1];
            cin >> vals[2];
            cin >> vals[3];
            cin >> vals[4];
            cin >> vals[5];
            cin >> value;
            TCarNumber cn = {{vals[0],vals[1], vals[2],vals[3],vals[4],vals[5]}};
            TKeyValuePair kvp(cn, value);
            pairs[size] = kvp;
            size++;
        }
        RadixSort(pairs, size, 0, size - 1, 0);
        for( int i = 0; i < size; i++) { 
            cout << pairs[i].Key.vals[0] << ' '
                << pairs[i].Key.vals[1] 
                << pairs[i].Key.vals[2] 
                << pairs[i].Key.vals[3] << ' '
                << pairs[i].Key.vals[4]
                << pairs[i].Key.vals[5]
                << '\t' << pairs[i].Value;
            cout << endl;
        }
        delete [] pairs;
    return 0; 
}