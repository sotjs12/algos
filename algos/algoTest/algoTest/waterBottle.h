#pragma once
#include <iostream>

using namespace std;

class waterBottle {
private:
	int bottleC=0;
	int target=0;
	int bottleCnt=0;
	int* status;
	int* beforeIdx;
	int* pows;
	int statusIdx = 0;
	int statusSize = 100;

	void resize_status() {
		int* temp;
		int* temp2;
		statusSize *= 2;
		temp = new int[statusSize];
		temp2 = new int[statusSize];
		for (int i = 0; i < statusIdx; ++i) {
			temp[i] = status[i];
			temp2[i] = beforeIdx[i];
		}
		delete status;
		delete beforeIdx;
		beforeIdx = temp2;
		status = temp;
	}
	void print(int idx) {
		if (idx == 0) {
			for (int i = 0; i < bottleCnt; ++i)
				cout << "0 ";
			cout << endl;
			return;
		}
		print(beforeIdx[idx]);
		int cur = status[idx];
		for (int i = 0; i < bottleCnt; ++i) 
			cout << ((cur / pows[i]) % 10) << " ";
		cout << endl;
	}
	int can_make_status(int from,int to,int type,int idx) {
		int cur = status[idx];
		int f, t,fc;
		int newStatus=cur;
		f = (cur / pows[from]) % 10;
		t = ((bottleC / pows[to])%10) - ((cur / pows[to]) % 10);
		fc = (bottleC / pows[from]) % 10;
		switch (type)
		{
		case 0:			// 다른물통에 붓기
			if (from == to)return -1;
			if (f <= t) {	//있는거 다붓기
				newStatus -= f*pows[from];
				newStatus += f*pows[to];
				break;
			}
			else {						//붓고 남기기
				newStatus -= t*pows[from];
				newStatus += t*pows[to];
				break;
			}
		case 1:			// 자기 꽉 체우기
			newStatus += (fc - f)*pows[from];
			break;			
		case 2:			// 물통 비우기
			newStatus -= f*pows[from];
			break;
		}

		for (int i = 0; i < statusIdx; ++i)
			if (status[i]== newStatus) return -1;
		return newStatus;
	}
	int enQueue_process(int idx) {
		int newStatus;
		for (int i = 0; i < bottleCnt; ++i) {
			for (int j = 0; j < bottleCnt; ++j) {
				for (int t = 0; t < 3; ++t) {
					if ((newStatus = can_make_status(i, j, t, idx)) != -1) {
						beforeIdx[statusIdx] = idx;
						status[statusIdx++] = newStatus;
						if (target == newStatus) return statusIdx-1;
						if (statusIdx == statusSize) resize_status();
					}
				}
			}
		}
		return -1;
	}
	void process() {
		int idx=0;
		int successIdx;
		while ( idx < statusIdx) {
			if ((successIdx = enQueue_process(idx++)) != -1) {
				cout << endl;
				print(successIdx);
				break;
			}
		}
	}
public:
	void run() {
		int idx = 0,t,t2,ten=1;
		cin >> bottleCnt;
		beforeIdx = new int[statusSize];
		status = new int[statusSize];
		pows = new int[bottleCnt];
		status[0] = 0;
		for (idx = 0; idx < bottleCnt; ++idx,ten *= 10) {
			pows[idx] = ten;
			cin >> t>>t2;
			bottleC += t*ten;
			status[0] += t2*ten;
		}
		statusIdx++;
		for (idx = 0; idx < bottleCnt; ++idx) {
			cin >> t;
			target += t*pows[idx];
		}
		process();
	}
};