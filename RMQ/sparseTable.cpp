#include <iostream>
#include <time.h>
#include <limits>
using namespace std;

const int SIZE = 100;
const int SIZELOG = 7;

int Fl(int len) {
	if (len <= 1) {
		return 0;
	}
	else {
		return Fl(len / 2) + 1;
	}
}

int Min(int a, int b) {
	return ((a > b) ? b : a);
}

int numbers[SIZE];

int sparseTable[SIZE][SIZELOG];

void BuildST() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZELOG; j++) {
			sparseTable[i][j] = numeric_limits<int>::max();
		}
	}
	for (int i = SIZE - 1; i >=0; i--) {
		int power = 1;
		for (int j = 0; j < SIZELOG; j++) {
			if (j > 0) {
				sparseTable[i][j] = Min(sparseTable[i][j - 1], sparseTable[i + power][j - 1]);
				power *= 2;
			}
			else {
				sparseTable[i][j] = numbers[i];
			}
		}
	}
}

int Power(int p) {
	if (p > 0) {
		return Power(p - 1)*2;
	}
	else {
		return 1;
	}
}

int LogLength[SIZE + 1];
int Powers[SIZELOG];

void CalcLog() {
	for (int i = 0; i <= SIZE; i++) {
		LogLength[i] = Fl(i);
	}
	for (int i = 0; i < SIZELOG; i++) {
		Powers[i] = Power(i);
	}
}

int FindMin(int l, int r) {
	int j = LogLength[r - l + 1];
	return Min(sparseTable[l][j], sparseTable[r - Powers[j] + 1][j]);
}

int FindMinN(int l, int r) {
	int min = numeric_limits<int>::max();
	for (int i = l; i <= r; i++) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	return min;
}

int main()
{
	srand(time(0));
	for (int i = 0; i < SIZE; i++) {
		numbers[i] = rand()%1000;
	}
	CalcLog();
	BuildST();
	for (int l = 0; l < SIZE; l++) {
		for (int r = l; r < SIZE; r++) {
			int res = FindMin(l, r);
			int resN = FindMinN(l, r);
			cout << (res == resN) << endl;
			if (res != resN) {
				int v = 0;
				v--;
			}
		}
	}
	
    return 0;
}