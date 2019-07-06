#include "lab1.h"
using namespace std;

KeyValuePair::KeyValuePair(CarNumber key, unsigned long long value) {
    Key = key;
    Value = value;
}
KeyValuePair::KeyValuePair() {
    
}


void RadixSort(KeyValuePair pairs[], size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];

    KeyValuePair *nextArray = new KeyValuePair[size];

    memcpy(nextArray, pairs, size*sizeof(KeyValuePair));

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
        memcpy(pairs, nextArray, size*sizeof(KeyValuePair));
    }
    delete [] nextArray;
}

int main(int argc, char *argv[]) {
    if(argc != ARGUMENT_COUNT) {
        cout << "Use [command] [inFile] [outFile]" << endl;
        return 0;
    }
    try {
        ifstream inFile(argv[1]);
        if(!inFile.is_open()) {
            cout << "unable to open file " << argv[1] << endl;
            return 0;
        }
        size_t size = 0;
        size_t currSize = 1;
        KeyValuePair* pairs = new KeyValuePair[currSize];
        while (!inFile.eof()) {
            if(currSize==size) {
                KeyValuePair* temp = new KeyValuePair[2 * currSize];
                copy(pairs, pairs + currSize, temp);
                currSize *= 2;
                delete [] pairs;
                pairs = temp;
            }

            unsigned char vals[NUMBER_OF_DIGITS];
            unsigned long long value = 0;
            inFile >> vals;
            inFile >> value;
            CarNumber cn = {{vals[0],vals[1], vals[2],vals[3],vals[4],vals[5]}};
            KeyValuePair kvp(cn, value);
            pairs[size] = kvp;
            size++;
        }
        inFile.close();
        RadixSort(pairs, size);
        ofstream outFile(argv[2]);
        if(!outFile.is_open()) {
            cout << "unable to open file " << argv[2] << endl;
            return 0;
        }
        for( int i = 0; i < size; i++) { 
            outFile << pairs[i].Key.vals << '\t' << pairs[i].Value;
            if((i+1) != size)
                outFile << endl;
        }
        outFile.close();
        delete [] pairs;
    }
    catch(bad_alloc& ex) {
        cerr  << "Out of memory!";
        cin.get();
        exit(1);
    }
    return 0; 
}