#include <iostream>
#include <fstream>
using namespace std;

int Min(int a, int b) {
    return (a < b) ? a : b;
}
int Min(int a, int b, int c) {
    return (Min(a,b) < Min(b,c)) ? Min(a,b) : Min(b,c);
}

int main(int argc, char *argv[]) {
	ifstream inFile(argv[1]);
    int n = 0;
    inFile >> n;
    inFile.close();
    
    int* arr = new int[n+1];
    arr[0] = 0;
    arr[1] = 0;
    for ( int i = 2; i <= n; i++ ) {
        if(i % 6 == 0){ 
            arr[i] = i + Min(arr[i - 1], arr[i / 2], arr[i / 3]);
        }
        else if (i % 3 == 0) {
            arr[i] = i + Min(arr[i / 3], arr[i - 1]);
        }
        else if (i % 2 == 0) {
            arr[i] = i + Min(arr[i / 2], arr[i - 1]);
        }
        else {
            arr[i] = i + arr[i - 1];
        }
    }
    ofstream outFile(argv[2]);
    outFile << arr[n] << endl;
    for( int i = n; i != 1; ) {
        if(i % 6 == 0){ 
            if(arr[i / 3] <= arr[i / 2] && arr[i / 3] <= arr[i - 1]) {
                outFile << "/3 ";
                i /= 3;
            }
            else if(arr[i / 2] <= arr[i / 3] && arr[i / 2] <= arr[i - 1]) {
                outFile << "/2 ";
                i /= 2;
            }
            else {
                outFile << "-1 ";
                i--;
            }
        }
        else if (i % 3 == 0) {
            if(arr[i / 3] <= arr[i - 1]) {
                outFile << "/3 ";
                i /= 3;
            }
            else {
                outFile << "-1 ";
                i--;
            }
        }
        else if (i % 2 == 0) {
            if(arr[i / 2] <= arr[i - 1]) {
                outFile << "/2 ";
                i /= 2;
            }
            else {
                outFile << "-1 ";
                i--;
            }
        }
        else {
            outFile << "-1 ";
            i--;
        }
    }
    outFile << endl;
    
    outFile.close();
    delete[] arr;
}