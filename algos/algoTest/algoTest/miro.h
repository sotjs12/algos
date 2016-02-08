#pragma once
#include <iostream>
#include <vector>
using namespace std;

#define WALL 1
#define WAY 0
#define START 2
#define END 3
#define MOVED -1
#define WAY_CASE 4
class Miro {
private:
	int xS;
	int yS;
	int start;
	int end;
	int move;
	int curve;
	int minMoveIdx = 0;
	int minCurveIdx = 0;
	int minMove = -1;
	int minCurve = -1;
	int** board;
	vector<int**> maps;
	int xCase[WAY_CASE] = { 0,1,0,-1 };
	int yCase[WAY_CASE] = { -1,0,1,0 };
public:
	Miro(int X, int Y) {
		xS = X;
		yS = Y;
		board = new int*[yS];
		for (int y = 0; y < yS; ++y)
			board[y] = new int[xS];
		move = 0;
		curve = -1;
	}
	void init() {
		int val;
		for (int y = 0; y < yS; ++y) {
			for (int x = 0; x < xS; ++x) {
				cin >> val;
				board[y][x] = val;
				if (val == START)
					start = x + y*xS;
				else if (val == END)
					end = x + y*xS;
			}
		}
		find_way(start % xS, start / xS);
		cout << endl << minMove << " " << minCurve << endl;
		print(minMoveIdx);
		print(minCurveIdx);
	}
	void print(int idx) {
		if (maps.empty()) return;
		int** arr = maps[idx];
		for (int y = 0; y < yS; ++y) {
			for (int x = 0; x < xS; ++x) {
				cout.width(2);
				cout << arr[y][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void save_map() {
		if (minMove == -1 && minCurve == -1) {
			minMove = move;
			minCurve = curve;
		}
		if (minMove > move) {
			minMove = move;
			minMoveIdx = maps.size();
		}
		if (minCurve > curve) {
			minCurve = curve;
			minCurveIdx = maps.size();
		}
		int** map = new int*[yS];
		for (int y = 0; y < yS; ++y) {
			map[y] = new int[xS];
			for (int x = 0; x < xS; ++x) {
				map[y][x] = board[y][x];
			}
		}
		maps.push_back(map);
	}
	bool find_way(int x, int y) {
		if (board[y][x] == END) {
			save_map();
			return false;
		}
		for (int i = 0; i < WAY_CASE; ++i) {
			if (can_go(x + xCase[i], y + yCase[i])) {
				move++;
				if (board[y][x] != START) board[y][x] = MOVED;
				if (is_curve(x - xCase[i], y - yCase[i])) curve++;
				if (find_way(x + xCase[i], y + yCase[i])) return true;
				else {
					board[y][x] = WAY;
					if (is_curve(x - xCase[i], y - yCase[i]))	curve--;
					move--;
				}
			}
		}
		return false;
	}
	bool is_curve(int x, int y) {
		if ((x >= 0 && x < xS) && (y >= 0 && y < yS))
			if (board[y][x] == MOVED)
				return false;
		return true;
	}
	bool can_go(int x, int y) {
		if ((x >= 0 && x < xS) && (y >= 0 && y < yS))
			if (board[y][x] != WALL && board[y][x] != MOVED)
				return true;
		return false;
	}

};