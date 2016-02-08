#pragma once
#include <iostream>
using namespace std;

#define WAY_CASE 4
#define WATER -1
#define LAND 0

class Node {
public:
	int x;
	int y;
	Node(int X, int Y) {
		x = X;
		y = Y;
	}
};
const int MAX_SIZE = 3000;
class Queue {
private:
	Node* q[MAX_SIZE + 1];
	int front = 0;
	int end = MAX_SIZE - 1;
	int cnt = 0;
public:
	Queue() {}
	void push(int x, int y) {
		if (cnt >= MAX_SIZE) {
			cout << "overfolw" << endl;
			return;
		}
		Node* node = new Node(x, y);
		end = (end + 1) % MAX_SIZE;
		q[end] = node;
		cnt++;
	}
	Node* pop() {
		if (cnt <= 0)
			return NULL;
		int temp = front;
		front = (front + 1) % MAX_SIZE;
		cnt--;
		return q[temp];
	}
	bool isEmpty() {
		if (cnt == 0)
			return true;
		return false;
	}
};

class Island {
private:
	int islandIdx = 1;
	int n;
	Queue ways;
	int** map;
	int xCase[WAY_CASE] = { 0,1,0,-1 };
	int yCase[WAY_CASE] = { -1,0,1,0 };
public:
	Island() {}
	void run() {
		cin >> n;
		map = new int*[n];
		for (int y = 0; y < n; ++y) {
			map[y] = new int[n];
			for (int x = 0; x < n; ++x)
				cin >> map[y][x];
		}
		for (int y = 0; y < n; ++y)
			for (int x = 0; x < n; ++x)
				if (map[y][x] == LAND) {
					ways.push(x, y);
					find_island();
					islandIdx++;
				}
		print();
	}
	void print() {
		cout << "ÃÑ ¼¶¼ö : " << islandIdx - 1 << endl;
		for (int y = 0; y < n; ++y) {
			for (int x = 0; x < n; ++x) {
				cout.width(3);
				cout << map[y][x];
			}
			cout << endl;
		}
	}
	void find_island() {
		Node* node = NULL;
		int x, y;
		while (!ways.isEmpty()) {
			node = ways.pop();
			x = node->x;
			y = node->y;
			map[y][x] = islandIdx;
			for (int i = 0; i < WAY_CASE; ++i)
				if (is_land(x + xCase[i], y + yCase[i]))
					ways.push(x + xCase[i], y + yCase[i]);
		}
	}
	bool is_land(int x, int y) {
		if ((x >= 0 && x < n) && (y >= 0 && y < n))
			if (map[y][x] == LAND)
				return true;
		return false;
	}
};