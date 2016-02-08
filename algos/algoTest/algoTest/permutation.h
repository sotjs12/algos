#pragma once
#include <iostream>

using namespace std;

class Permutation {
private:
	int nSize;
	int mSize;
	int* arr;
	int* result;
	bool* checkUsed;
public:
	Permutation() {}
	void init(int n, int m) {
		nSize = n;
		mSize = m;
		arr = new int[nSize];
		result = new int[mSize];
		checkUsed = new bool[nSize];
		for (int i = 0; i < n; ++i) {
			arr[i] = i + 1;
			checkUsed[i] = false;
		}

	}
	void print() {
		for (int i = 0; i < mSize; ++i)
			cout << result[i];
		cout << endl;
	}
	void generate(int m) {
		if (m == mSize)
			print();
		else {
			for (int i = 0; i < nSize; ++i) {
				if (!checkUsed[i]) {
					checkUsed[i] = true;
					result[m] = arr[i];
					generate(m + 1);
					checkUsed[i] = false;
				}
			}
		}
	}
};