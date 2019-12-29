#include "main.h"
#include <string>
using namespace std;

TKeyValuePair::TKeyValuePair(TCarNumber key, string value) {
    Key = key;
    Value = value;
}
TKeyValuePair::TKeyValuePair() {
    
}


void RadixSort(TKeyValuePair pairs[], size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];

    TKeyValuePair *nextArray = new TKeyValuePair[size];

    memcpy(nextArray, pairs, size*sizeof(TKeyValuePair));

    for (int i = NUMBER_OF_DIGITS-1; i >= 0; --i) {
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            countArray[j] = 0;
        }

        for (int j = 0; j < size; ++j) {
            unsigned char d = pairs[j].Key.vals[i];
            countArray[d]++;                                     // countArray[d] - число элементов, у который  i-ый разряд - цифра d
        }

        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;                                 // новые индексы при сортировке по i-ому разряду
            count += tmp;
        }

        for (int j = 0; j < size; ++j) {
            unsigned char d = pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];   // здесь сохраняется относительный порядок пар с одинаковыми ключами, так как самый первый из pairs будет 
            countArray[d]++;                       // самым первым в nextArray, второй будет вторым в nextArray и т.д. до последнего.
        }
        memcpy(pairs, nextArray, size*sizeof(TKeyValuePair));
    }
    delete [] nextArray;
}

int main(int argc, char *argv[]) {
        size_t size = 0;
        size_t currSize = 1;
        TKeyValuePair* pairs = new TKeyValuePair[currSize];
        while (!cin.eof()) {
            if(currSize==size) {
                TKeyValuePair* temp = new TKeyValuePair[2 * currSize];
                copy(pairs, pairs + currSize, temp);
                currSize *= 2;
                delete [] pairs;
                pairs = temp;
            }

            unsigned char vals[NUMBER_OF_DIGITS];

            unsigned long long value = 0;
            cin >> vals[0];
            cin >> vals[1];
            cin >> vals[2];
            cin >> vals[3];
            cin >> vals[4];
            cin >> vals[5];
            string t;
            cin >> t;
            TCarNumber cn = {{vals[0],vals[1], vals[2],vals[3],vals[4],vals[5]}};
            TKeyValuePair kvp(cn, t);
            pairs[size] = kvp;
            size++;
        }
        RadixSort(pairs, size);
        for( int i = 0; i < size; i++) { 
            cout << pairs[i].Key.vals << '\t' << pairs[i].Value;
            if((i+1) != size)
                cout << endl;
        }
        delete [] pairs;
    return 0; 
}