#include <iostream>

int Min(int a, int b) {
    return (a < b) ? a : b;
}
int Min(int a, int b, int c) {
    return (Min(a,b) < Min(b,c)) ? Min(a,b) : Min(b,c);
}

int main(int argc, char *argv[]) {
    int n = 0;
    std::cin >> n; 
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
    std::cout << arr[n] << std::endl;
    for( int i = n; i != 1; ) {
        if(i != n) {
            std::cout << ' ';
        }
        if(i % 6 == 0){ 
            if(arr[i / 3] <= arr[i / 2] && arr[i / 3] <= arr[i - 1]) {
                std::cout << "/3";
                i /= 3;
            }
            else if(arr[i / 2] <= arr[i / 3] && arr[i / 2] <= arr[i - 1]) {
                std::cout << "/2";
                i /= 2;
            }
            else {
                std::cout << "-1";
                i--;
            }
        }
        else if (i % 3 == 0) {
            if(arr[i / 3] <= arr[i - 1]) {
                std::cout << "/3";
                i /= 3;
            }
            else {
                std::cout << "-1";
                i--;
            }
        }
        else if (i % 2 == 0) {
            if(arr[i / 2] <= arr[i - 1]) {
                std::cout << "/2";
                i /= 2;
            }
            else {
                std::cout << "-1";
                i--;
            }
        }
        else {
            std::cout << "-1";
            i--;
        }
    }
    std::cout << std::endl;
    delete[] arr;
}