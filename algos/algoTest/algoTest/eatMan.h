#pragma once
#include <iostream>
#include <list>
using namespace std;

#define MAXSIZE 10000
class EatNode {
public:
	int eat;
	int man;
	int eats;
	int mans;
	bool toRight;
	char* path;
	EatNode(int EAT, int MAN,int Eats,int Mans,bool flag) {
		eat = EAT;
		man = MAN;
		toRight = flag;
		eats = Eats;
		mans = Mans;
	}
	EatNode(int EAT, int MAN, int Eats, int Mans,char* p, bool flag) {
		eat = EAT;
		man = MAN;
		toRight = flag;
		eats = Eats;
		mans = Mans;
		path = p;
	}
};
class EatQueue {
private:
	EatNode* q[MAXSIZE + 1];
	int front = 0;
	int end = MAXSIZE - 1;
	int cnt = 0;
public:
	EatQueue() {}
	void push(int x, int y,int z,int k,bool flag) {
		if (cnt >= MAXSIZE) {
			cout << "overfolw" << endl;
			return;
		}
		EatNode* node = new EatNode(x, y,z,k,flag);
		end = (end + 1) % MAXSIZE;
		q[end] = node;
		cnt++;
	}
	EatNode* pop() {
		if (cnt <= 0)
			return NULL;
		int temp = front;
		front = (front + 1) % MAXSIZE;
		cnt--;
		return q[temp];
	}
	bool isEmpty() {
		if (cnt == 0)
			return true;
		return false;
	}
};
class EatMan {
private:
	bool** checkLeft;
	bool** checkRight;
	int eatSize;
	int manSize;
	int boatSize;
	int cnt = 0;
	char* result[1000];
	EatNode* bfs_result[1000];

	bool suck = false;

	bool canMoveLeft(int lEats, int lMans, int eat, int man) {
		if (suck)return false;
		if (eat + man > boatSize || (eat == 0 && man == 0))return false;
		if (man != 0 && man < eat)return false;
		if (lEats + eat > eatSize || lMans + man > manSize)return false;
		if (checkLeft[lEats + eat][lMans + man]) return false;
		if ((eatSize - lEats - eat > manSize - lMans - man) && manSize - lMans - man!= 0) return false;// 오른쪽에 남은사람 검사
		if (lEats +eat > lMans+man && lMans+man != 0)return false;	//왼쪽지역에서 살해검토
		return true;
	}
	bool canMoveRight(int lEats, int lMans, int eat, int man) {
		if (suck)return false;
		if (eat + man > boatSize || (eat == 0 && man == 0))return false;
		if (man != 0 && man < eat)return false;
		if (lEats - eat<0 || lMans - man<0)   return false;
		if (checkRight[lEats - eat][lMans - man]) return false;
		if ((eatSize - lEats + eat > manSize - lMans + man) && manSize - lMans + man != 0) return false;// 오른쪽에 남은사람 검사
		if (lEats - eat > lMans - man && lMans - man != 0)return false;	//왼쪽지역에서 살해검토
		return true;
	}

	void find_way(int lEats, int lMans, bool isRight) {
		int rEats = eatSize - lEats;
		int rMans = manSize - lMans;
		if (suck)
			return;
		if (rMans == 0 && rEats == 0) {
			suck = true;
			for (int i = 0; i < cnt; i++)
				cout << result[i];
			return;
		}
		for (int eat = boatSize; eat >= 0; --eat) {
			for (int man = boatSize; man >= 0; --man) {
				if (isRight) {
					if (canMoveLeft(lEats, lMans, eat, man)) {
						char* buf2 = new char[100];
						sprintf_s(buf2,100, "<- %d , %d %d/%d  %d/%d\n", man, eat, lMans + man, lEats + eat, rMans - man, rEats - eat);
						result[cnt++] = buf2;
						checkLeft[lEats + eat][lMans + man] = true;
						find_way(lEats + eat, lMans + man, !isRight);
						checkLeft[lEats + eat][lMans + man] = false;
						delete result[--cnt];
					}
				}
				else {
					if (canMoveRight(lEats, lMans, eat, man)) {
						char* buf2 = new char[100];
						sprintf_s(buf2, 100, "-> %d , %d %d/%d  %d/%d\n", man, eat, lMans - man, lEats - eat, rMans + man, rEats + eat);
						result[cnt++] = buf2;
						checkRight[lEats - eat][lMans - man] = true;
						find_way(lEats - eat, lMans - man, !isRight);
						checkRight[lEats - eat][lMans - man] = false;
						delete result[--cnt];
					}
				}
			}
		}		
	}
	void print_dfs(int next) {
		EatNode* n = bfs_result[next];
		if(next == 0)
			cout << bfs_result[next]->path;
		for (int i = next-1; i >= 0; --i) {
			if (!n->toRight) {
				if (((n->eats - n->eat) == bfs_result[i]->eats)
					&& ((n->mans - n->man) == bfs_result[i]->mans)
					&& (!n->toRight == bfs_result[i]->toRight)) {
					print_dfs(i);
					cout << bfs_result[next]->path;
					break;
				}
			}
			else {
				if (((n->eats + n->eat) == bfs_result[i]->eats)
					&& ((n->mans + n->man) == bfs_result[i]->mans)
					&& (!n->toRight == bfs_result[i]->toRight)) {
					print_dfs(i);
					cout << bfs_result[next]->path;
					break;
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
		find_way(0, 0, true);

		if (suck)cout << "성공" << endl;
		else cout << "실패" << endl;
	}
	void find_with_bfs();
	
};

void EatMan::find_with_bfs() {
	/////////////// 초기화코드 ////////////
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
	checkRight[eatSize][manSize] = checkRight[0][0] = checkLeft[0][0] = true;
	EatQueue q;
	EatNode* n;
	bool flag=true;
	bool moved;
	suck = false;
	int Eats = eatSize;
	int Mans = manSize;
	char* buf=NULL;
	cnt = 0;
	q.push(0, 0,0,0, flag);
	//////////////// /////////////////////

	while (!q.isEmpty() && !suck) {
		n = q.pop();
		flag = n->toRight;
		Eats = n->eats;
		Mans = n->mans;
		moved = false;
		for (int eat = boatSize; eat >= 0; --eat) {
			for (int man = boatSize; man >= 0 ; --man) {
				if (flag) {
					if (canMoveLeft(Eats, Mans, eat, man)) {
						moved = checkLeft[Eats + eat][Mans + man] = true;
						buf = new char[100];
						sprintf_s(buf, 100, "<- %d , %d %d/%d  %d/%d\n", man, eat, Mans + man, Eats + eat, manSize - Mans - man, eatSize - Eats - eat);
						bfs_result[cnt++] = new EatNode(eat, man, Eats + eat, Mans + man,buf, !flag);
						q.push(eat, man, Eats + eat, Mans + man, !flag);
						if (Eats + eat == eatSize && Mans + man == manSize)suck = true;
					}
				}
				else {
					if (canMoveRight(Eats, Mans, eat, man)) {
						moved = checkRight[Eats - eat][Mans - man] = true;
						buf = new char[100];
						sprintf_s(buf, 100, "-> %d , %d %d/%d  %d/%d\n", man, eat, Mans - man, Eats - eat, manSize - Mans + man, eatSize - Eats + eat);
						bfs_result[cnt++] = new EatNode(eat, man, Eats - eat, Mans - man, buf, !flag);
						q.push(eat, man, Eats - eat, Mans - man, !flag);
					}
				}
			}
		}
	}

	if (suck) {
		cout << endl;
		print_dfs(cnt-1);
		cout << "  성공" << endl;
	}
	else cout << "실패" << endl;
}
