#pragma once
#include <iostream>
using namespace std;

#define MOVE_CASE 8
class Knight {
private:
	int** check;
	int xMoveIdx[MOVE_CASE] = { -2,-2,-1,-1,1,1,2,2 };
	int yMoveIdx[MOVE_CASE] = { -1,1,-2,2,-2,2,-1,1 };
	int n;
public:
	Knight(int size) {
		n = size;
		check = new int*[n];
		for (int i = 0; i < n; i++) {
			check[i] = new int[n];
			for (int j = 0; j < n; j++)
				check[i][j] = -1;
		}
	}
	bool process(int x, int y, int cnt) {
		if (cnt == n*n - 1) {
			check[y][x] = cnt;
			print();
			return true;
		}
		for (int i = 0; i < MOVE_CASE; ++i) {
			if (moveAble(x + xMoveIdx[i], y + yMoveIdx[i])) {
				check[y][x] = cnt;
				if (process(x + xMoveIdx[i], y + yMoveIdx[i], cnt + 1))return true;
				else check[y][x] = -1;
			}
		}
		return false;
	}
	bool moveAble(int x, int y) {
		if ((x >= 0 && x < n) && (y >= 0 && y < n))
			if (check[y][x] == -1)
				return true;
		return false;
	}
	void print() {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				cout.width(3);
				if (check[y][x] == -1)cout << "x ";
				else cout << check[y][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
};