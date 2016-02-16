#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Edge {
public:
	int from;
	int to;
	int weight;
	Edge(int f, int t, int w) {
		from = f;
		to = t;
		weight = w;
	}
};
class Vertex {
public:
	int idx;
	int edgeCnt = 0;
	bool visited = false;
	Edge* ways[10];
	Vertex(int i) {
		idx = i;
		for (int i = 0; i < 10; ++i)ways[i] = NULL;
	}
	void addEdge(Edge* e) {
		ways[e->to] = e;
		edgeCnt++;
	}
};
class tsp1 {
private:
	int size;
	int startIdx;
	int weight = 0;
	Vertex** vertex;

	void solve(Vertex* v,int subWeight,int cnt) {
		if (cnt == size) {
			v->visited = false;
			if (v->ways[startIdx] == NULL)return;
			else if (weight > subWeight + v->ways[startIdx]->weight || weight == 0) 
				weight = subWeight + v->ways[startIdx]->weight;
			return;
		}
		v->visited = true;
		for (int i = 0; i < 10 ; ++i) {
			if (v->ways[i] == NULL)continue; 
			if (!vertex[i]->visited) {
				solve(vertex[i], subWeight + v->ways[i]->weight, cnt + 1);
			}
		}
		v->visited = false;
	}
public:
	void run() {
		int i, j,tmp;
		cin >> size;
		vertex = new Vertex*[size];
		for (i = 0; i < size; ++i) vertex[i] = new Vertex(i);

		for (i = 0; i < size; ++i) {
			for (j = 0; j < size; ++j) {
				cin >> tmp;
				if (i != j && tmp != 0) vertex[i]->addEdge(new Edge(i,j,tmp));
			}
		}
		for (i = 0; i < size; i++) {
			startIdx = i;
			solve(vertex[i], 0, 1);
		}
				
		cout << weight << endl;
	}
};

class coin1 {
private:
public:
	void run() {
		int i, j, cases, target;
		int* coins;
		int* mem;
		cin >> cases >> target;
		coins = new int[cases];
		mem = new int[target + 1];
		for (i = 0; i < cases; ++i) cin >> coins[i];
		for (i = 0; i <= target; ++i) mem[i] = 0;
		mem[0] = 1;
		sort(coins, coins + cases);
		for (i = 0; i < cases; ++i) 
			for (j = coins[i]; j <= target; ++j)
				mem[j] += mem[j - coins[i]];
		cout << mem[target] << endl;
	}
};
class cupNode {
public:
	int dead;
	int reward;
	cupNode(int d, int r) {
		dead = d;
		reward = r;
	}
};
bool compare_cup(cupNode* a, cupNode* b) {
	return a->reward > b->reward;
}
class cupRamen {
private:
	cupNode** arr;
	int* buf;
	int size;	
public:
	void run() {
		///// 초기화
		int dead, re, max = 0, bufSize = 0;;
		
		cin >> size;
		if (size < 1 || size >200000)return;
		arr = new cupNode*[size];
		for (int i = 0; i < size; ++i) {
			cin >> dead >> re;
			if (max < dead)max = dead;
			arr[i] = new cupNode(dead, re);			
		}
		sort(arr, arr + size, compare_cup);
		buf = new int[max+1];
		for (int i = 0; i < max; ++i) buf[i] = 0;

		for (int i = 0, idx = 0; i < size && bufSize != max; ++i) {
			idx = arr[i]->dead;
			re = arr[i]->reward;
			if (buf[idx] == 0) {
				buf[idx] = re;
				bufSize++;
			}
			else {
				for (int j = idx; j > 0; --j) {
					if (buf[j] == 0) {
						buf[j] = re;
						bufSize++;
						break;
					}
					else if (buf[j] < re) {
						buf[j] = re;
						break;
					}
				}
			}
		}
		re = 0;
		for (int i = 1; i <= max; ++i) re += buf[i];
		cout << re << endl;
	}
};

class topDown {
private:
	int* origin;
	int* min;
	int* max;
	int* min2;
	int* max2;
	int size;

	void process() {
		int j, m, mx;
		////////////// min	 첫데이터넣기
		if (min[0] > min[1]) m = min[1];
		else m = min[0];
		min2[0] = m + origin[0];
		min2[1] = m + origin[1];
		//////////////// max
		if (max[0] < max[1]) mx = max[1];
		else mx = max[0];
		max2[0] = mx + origin[0];
		max2[1] = mx + origin[1];

		for (j = 2; j < size; ++j) {
			/////////////min
			if (min[j - 1] > min[j]) m = min[j];
			else m = min[j - 1];
			if (m + origin[j - 1] < min2[j - 1])
				min2[j - 1] = m + origin[j - 1];
			min2[j] = m + origin[j];
			//////////////////max
			if (max[j - 1] < max[j]) mx = max[j];
			else mx = max[j - 1];
			if (mx + origin[j - 1] > max2[j - 1])
				max2[j - 1] = mx + origin[j - 1];
			max2[j] = mx + origin[j];
		}
		for (j = 0; j < size; ++j) {
			min[j] = min2[j];
			max[j] = max2[j];
		}
	}
public:
	void run() {
		int i, j;
		int m = -1, mx = 0;
		int size2;
		cin >> size2;
		size = 3;
		origin = new int[size];
		min = new int[size];
		min2 = new int[size];
		max = new int[size];
		max2 = new int[size];
		for (j = 0; j < size; ++j) {
			cin >> origin[j];
			min2[j] = max2[j] = min[j] = max[j] = origin[j];
		}
		for (i = 1; i < size2; ++i) {
			for ( j = 0; j < size; ++j) cin >> origin[j];
			process();
		}
		for ( i = 0; i < size; ++i) {
			if (max[i] > mx)mx = max[i];
			if (min[i] < m || m == -1)m = min[i];
		}
		cout << mx << " " << m << endl;
	}
};

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