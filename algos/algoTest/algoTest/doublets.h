#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Doublets {
private:
	static const int MAX_WORD = 25143;
	static const int MAX_LEN = 16;

	vector<string> dictionary;
	map<string,int> dictionaryIdx;
	vector<string> results;
	vector<string> tempResult;
	vector<string> ft;
	vector<string> tt;
	string fromText;
	string toText;
	int toIdx;
	int fromIdx;
	void init() {
		string text;
		char buf[MAX_LEN];
		int i = 0;
		while (true) {
			cin.getline(buf, MAX_LEN);
			text = buf;
			if (text.length() > MAX_LEN || text.length() <= 0)
				break;
			dictionary.push_back(text);
			dictionaryIdx[text] = i++;
		}
	}
	void findDublets(int cur) {
		if (cur == toIdx) {
			if (tempResult.size() < results.size() || results.empty()) {
				tempResult.push_back(dictionary[cur]);
				results.clear();
				results.assign(tempResult.begin(),tempResult.end());
			}
			return;
		}
		for (int i = toIdx; i >= cur; --i) {
			if (isDublet(cur, i)) {
				tempResult.push_back(dictionary[cur]);
				findDublets(i);
				tempResult.pop_back();
			}
		}
	}
	bool isDublet(int cur,int to) {
		string t1 = dictionary[cur];
		string t2 = dictionary[to];
		if (t1.length() != t2.length())
			return false;
		int j = 0;
		for (int i = 0; i < t1.length(); ++i) {
			if (t1[i] != t2[i])
				++j;
		}
		if (j == 1)
			return true;
		return false;
	}
public:
	void run() {
		init();		
		char buf[MAX_LEN*2+2];
		string temps;
		while (true) {
			cin.getline(buf, MAX_LEN * 2 + 2);
			temps = buf;
			if (temps.length() == 0)
				break;
			fromText = temps.substr(0, (temps.length() / 2));
			toText = temps.substr((temps.length() / 2) + 1, temps.length());
			ft.push_back(fromText);
			tt.push_back(toText);			
		}
		for (int i = 0; i < ft.size(); ++i) {
			fromText = ft[i];
			toText = tt[i];
			if ((dictionaryIdx.find(fromText) == dictionaryIdx.end() || dictionaryIdx.find(toText) == dictionaryIdx.end()) || (dictionaryIdx[fromText] >= dictionaryIdx[toText])) {
				cout << "No solution." << endl<<endl;
				continue;
			}
			toIdx = dictionaryIdx[toText];
			fromIdx = dictionaryIdx[fromText];
			results.clear();
			tempResult.clear();
			findDublets(fromIdx);
			if (results.size() == 0) {
				cout << "No solution." << endl << endl;
				continue;
			}
			for (int i = 0; i < results.size(); ++i) {
				cout << results[i] << endl;
			}
			cout << endl;
		}
	}
};