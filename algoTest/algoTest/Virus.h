#pragma once
#include <iostream>
#include <queue>
#include <set>
#include <string>

using namespace std;

class Virus {
private:
	set<int> mem;
	bool flag = false;
	void BFS_Virus(int vCnt, int t);
public:
	void DFS_Virus(int vCnt, int t, string resul);
};

void Virus::BFS_Virus(int vCnt, int t) {
	queue<int> buf;
	queue<string> bufResult;
	string bufFront = "";
	buf.push(vCnt);
	bufResult.push(bufFront);
	cout << bufResult.front() << endl;
	while (!buf.empty()) {
		bufFront = bufResult.front();
		if (t == buf.front()) {
			cout << vCnt << bufFront << " = " << t << endl;
			break;
		}
		buf.push(buf.front() * 2);
		bufResult.push(bufFront + " x 2");
		buf.push(buf.front() / 3);
		bufResult.push(bufFront + " / 3");
		buf.pop();
		bufResult.pop();
		while (buf.front() == 0) {
			buf.pop();
			bufResult.pop();
		}
	}
}

void Virus::DFS_Virus(int vCnt, int t, string result)
{
	if (vCnt == 0 || flag)
		return;
	if (vCnt == t) {
		cout << result << " = " << t << endl;
		flag = true;
		return;
	}
	mem.insert(vCnt);
	//cout << vCnt << endl;
	if (mem.find(vCnt / 3) == mem.end())
		DFS_Virus(vCnt / 3, t, result + " / 3");
	if (mem.find(vCnt * 2) == mem.end())
		DFS_Virus(vCnt * 2, t, result + " * 2");

}