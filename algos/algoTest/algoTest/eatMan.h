#pragma once
#include <iostream>
#include <list>
using namespace std;

class EatMan {
private:
	bool** checkLeft;
	bool** checkRight;
	int eatSize;
	int manSize;
	int boatSize;
	list<string> results;
	bool suck = false;
	bool canMove(int lEat, int lMan, int rEat, int rMan) {
		if ((rEat>rMan) && rMan != 0) return false;
		if (lEat > lMan && lMan != 0)return false;
		return true;
	}

	void find_way(int lEats, int lMans, int rEats, int rMans, bool isRight) {
		if (suck)
			return;
		if (rMans == 0 && rEats == 0) {
			auto it = results.begin();
			while (it != results.end())
				cout << *(it++) << endl;
			suck = true;
			return;
		}
		string buf;
		char buf2[256];
		if (isRight) {
			for (int eat = boatSize; eat >= 0; --eat) {
				for (int man = boatSize; man >= 0; --man) {
					if (eat + man > boatSize || (eat == 0 && man == 0))continue;
					if (man != 0 && man < eat)continue;
					if (lEats + eat > eatSize || lMans + man > manSize)   continue;
					if (checkLeft[lEats + eat][lMans + man]) continue;
					if (canMove(lEats + eat, lMans + man, rEats - eat, rMans - man)) {
						checkLeft[lEats + eat][lMans + man] = true;
						sprintf_s(buf2, "<- %d , %d %d/%d  %d/%d\n", man, eat, lMans + man, lEats + eat, rMans - man, rEats - eat);
						buf = buf2;
						results.push_back(buf);
						find_way(lEats + eat, lMans + man, rEats - eat, rMans - man, !isRight);
						results.pop_back();
						checkLeft[lEats + eat][lMans + man] = false;
					}
				}
			}
		}
		else {
			for (int eat = boatSize; eat >= 0; --eat) {
				for (int man = boatSize; man >= 0; --man) {
					if (eat + man > boatSize || (eat == 0 && man == 0))continue;
					if (man != 0 && man < eat)continue;
					if (lEats - eat<0 || lMans - man<0)   continue;
					if (checkRight[lEats - eat][lMans - man]) continue;
					if (canMove(lEats - eat, lMans - man, rEats + eat, rMans + man)) {
						checkRight[lEats - eat][lMans - man] = true;
						sprintf_s(buf2, "-> %d , %d %d/%d  %d/%d\n", man, eat, lMans - man, lEats - eat, rMans + man, rEats + eat);
						buf = buf2;
						results.push_back(buf);
						find_way(lEats - eat, lMans - man, rEats + eat, rMans + man, !isRight);
						results.pop_back();
						checkRight[lEats - eat][lMans - man] = false;
					}
				}
			}
		}

	}
public:
	void run() {
		cout << "식인 : "; cin >> eatSize;
		cout << "일반 : "; cin >> manSize;
		cout << " 보트 크기 : "; cin >> boatSize;

		checkLeft = new bool*[eatSize + 1];
		checkRight = new bool*[eatSize + 1];
		for (int i = 0; i < eatSize + 1; ++i) {
			checkLeft[i] = new bool[manSize + 1];
			checkRight[i] = new bool[manSize + 1];
			for (int j = 0; j < manSize + 1; ++j)
				checkRight[i][j] = checkLeft[i][j] = false;
		}
		checkRight[0][0] = checkLeft[0][0] = true;
		find_way(0, 0, eatSize, manSize, true);

		if (suck)cout << "성공" << endl;
		else cout << "실패" << endl;
	}
};