#pragma once
#include <iostream>
#include <string> 
using namespace std;

class WERTYU {
private:
	string qwerty[4] = { "`1234567890-=","QWERTYUIOP[]\\","ASDFGHJKL;\'" ,"ZXCVBNM,./"};
public:
	void run() {
		string text;
		char* buf = new char[1024];

		while (!feof(stdin)) {
			if (!cin.getline(buf, 1024))
				break;
			text = buf;
			for (size_t i = 0; i < text.size(); ++i) {
				if (text[i] != ' ')
					for (int j = 0; j < 4; ++j) {
						size_t idx = qwerty[j].find(text[i]);
						if (idx != -1 && idx != 0) {
							text[i] = qwerty[j][idx - 1];
							break;
						}
					}
			}
			cout << text << endl;
		}
	}
};