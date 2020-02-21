#include "lab1.h"
using namespace std;
 
TKeyValuePair::TKeyValuePair(TCarNumber key, unsigned long long value) {
    Key = key;
    Value = value;
}
TKeyValuePair::TKeyValuePair() {
 
}
 
 
void RadixSort(TKeyValuePair pairs[], size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];
 
    TKeyValuePair *nextArray = new TKeyValuePair[size];
 
    memcpy(nextArray, pairs, size * sizeof(TKeyValuePair));
 
    for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            countArray[j] = 0;
        }
        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            countArray[d]++;                                     // countArray[d] - число элементов, у который  i-ый разряд - цифра d
        }
        
 
        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;                                 // новые индексы при сортировке по i-ому разряду
            count += tmp;
        }
        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];   // здесь сохраняется относительный порядок пар с одинаковыми ключами, так как самый первый из pairs будет 
            countArray[d]++;                       // самым первым в nextArray, второй будет вторым в nextArray и т.д. до последнего.
        }
        memcpy(pairs, nextArray, size * sizeof(TKeyValuePair));
    }
    delete[] nextArray;
}
 
int main(int argc, char *argv[]) {
    size_t size = 0;
    unsigned long long currSize = 1;
    TKeyValuePair* pairs = new TKeyValuePair[currSize];
    char val0;
    while (cin >> val0) {
        if (currSize == size) {
            pairs = (TKeyValuePair*)realloc(pairs, currSize * 2 * sizeof(TKeyValuePair));
            currSize *= 2;
        }
        TKeyValuePair kvp;
        unsigned char vals[NUMBER_OF_DIGITS];
        vals[0] = val0;
        cin >> vals[1];
        cin >> vals[2];
        cin >> vals[3];
        cin >> vals[4];
        cin >> vals[5];
        cin >> kvp.Value;
        TCarNumber cn = { { vals[0],vals[1], vals[2],vals[3],vals[4],vals[5] } };
        kvp.Key = cn;

        pairs[size] = kvp;
        size++;
    }
    
    RadixSort(pairs, size);
    
    

    for (size_t i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%llu\n",pairs[i].Key.vals[0],
            pairs[i].Key.vals[1],
            pairs[i].Key.vals[2],
            pairs[i].Key.vals[3],
            pairs[i].Key.vals[4],
            pairs[i].Key.vals[5],
            pairs[i].Value
            );
    }
    delete[] pairs;
    return 0;
}