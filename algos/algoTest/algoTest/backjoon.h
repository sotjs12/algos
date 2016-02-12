#pragma once
#include <iostream>
#include <vector>
using namespace std;


class ureka {
private:
	int* arr;
	int* inCase;
	int maxSize=0;
	int caseCnt;
	
	bool find_num(int idx,int num,int depth) {
		if (depth < 0)return false;
		if (depth == 0 && num == 0)	return true;
		for (int i = idx; i > 0; i=arr[i-1]) 
			if (find_num(arr[num - arr[i]], num - arr[i],depth-1))return true;		
		return false;
	}
	
	void make_arr() {
		int before = 1, val = 1;
		arr = new int[maxSize + 1];
		for (int i = 0,k=2; i < maxSize+1; ++i) {
			if (i == val) {
				before = arr[i] = val;
				val = (k*(k + 1)) / 2;
				k++;
			}
			else arr[i] = before;
		}
		arr[0] = 0;
	}
public:
	void run() {
		cin >> caseCnt;
		inCase = new int[caseCnt];		
		for (int i = 0; i < caseCnt; ++i) {	//max찾을겸 케이스도받고
			cin>> inCase[i];
			if (inCase[i] < 3 || inCase[i]>1000)return;
			if (inCase[i] > maxSize)maxSize = inCase[i];
		}	
		make_arr();					//삼각수 만들고
		for (int i = 0; i < caseCnt; ++i) {	//결과값을 찾아보자
			if (find_num(arr[inCase[i]],inCase[i],3)) cout << "1" << endl;
			else cout << "0" << endl;
		}
	}
};

class plus123 {
private:
	int cnt = 0;
	void cnt123(int num) {
		if (num == 0)cnt++;
		for (int i = 1; i <= 3 && num > 0; ++i)cnt123(num - i);
	}
public:
	void run() {
		int caseCnt;
		int* casearr;
		cin >> caseCnt;
		casearr = new int[caseCnt];
		for (int i = 0; i < caseCnt; ++i)cin >> casearr[i];
		for (int i = 0; i < caseCnt; ++i,cnt=0){
			cnt123(casearr[i]);
			cout << cnt << endl;
		}
	}
};

class teach {
private:
	int* arrCnt;
	bool** arr;
	bool origin[26];
	int max = 0, cur = 0, wordCnt, alpaCnt;
	vector<int> idxs;
	vector<int> temp;
	vector<vector<int>> idxs2;
	void make_combination(int idx,int depth) {
		if (max == wordCnt)return;
		if (depth == 0) {
			int cnt = 0;
			cur = 0;
			for (int i = 0; i < wordCnt; ++i) {
				if (alpaCnt < arrCnt[i])continue;
				cnt = 0;
				for (int j = 0; j < temp.size(); ++j)
					if (arr[i][temp[j]])cnt++;

				if (cnt == arrCnt[i])cur++;
			}
			if (max < cur)max = cur;
			return;
		}
		for (int i = idx; i < idxs.size(); ++i) {
			temp.push_back(idxs[i]);
			make_combination(i + 1, depth - 1);
			temp.pop_back();
		}
	}
public:
	bool run() {
		char buf[16], temp;
		int cnt = 0, idx = 0;
		cin >> wordCnt >> alpaCnt;
		if (wordCnt > 50 || wordCnt < 0)return false;
		if (alpaCnt > 26)return false;
		if ((alpaCnt -= 5) < 0)return false;
		arr = new bool*[wordCnt];
		arrCnt = new int[wordCnt];
		for (int i = 0; i < wordCnt; ++i, idx = 0) {
			arr[i] = new bool[26];
			arrCnt[i] = 0;
			for (int k = 0; k < 26; ++k)arr[i][k] = false;
			cin >> buf;
			while (buf[idx] != NULL) {
				temp = buf[idx++];
				if (temp != 'a' && temp != 'n' && temp != 'c' && temp != 't' && temp != 'i') {
					if (!arr[i][temp - 97])arrCnt[i]++;
					if (!origin[temp - 97])idxs.push_back(temp - 97);
					origin[temp - 97] = arr[i][temp - 97] = true;
				}
			}
			if (idx < 8 || idx >15)return false;
		}
		int in;
		if (idxs.size() > alpaCnt)in = alpaCnt;
		else in = (int)idxs.size();
		make_combination(0,in);
		
		cout << max<<endl;
		return true;
	}
};