#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <bitset>
#include "map.h"
using namespace std;
string xor (string e, string f) {
	string endxor;
	if (e.size() == f.size()) {
		endxor = e;
		for (int i = 0; i < e.size(); i++) {
			endxor[i] = '0';
			if (e[i] == '1') {
				if (e[i] != f[i]) {
					endxor[i] = '1';
				}
			}
			if (f[i] == '1') {
				if (f[i] != e[i]) {
					endxor[i] = '1';
				}
			}
		}
		return endxor;
	}
	else {
		return "Invalid Input";
	}
}
string decode(string code, int shift) {
	for (int i = 0; i < code.size(); i++) {
		code[i] -= shift;
		if (code[i] < 97) {
			code[i] += 26;
		}
	}
	return code;
}
string enc(string inp, bool proc) {
	string encout;
	for (int i = 0; i < inp.size(); i++) {
		bitset<8U> enctempone;
		string enctemptwo;
		enctempone = bitset<8>(inp[i]);
		enctemptwo = enctempone.to_string();
		encout = encout + enctemptwo;
	}
	string s = encout;
	string half = s.substr(0, s.length() / 2);
	string otherHalf = s.substr(s.length() / 2);
	if (proc == true) {
		cout << "This is the pre-encryption string: " << encout << endl;
		cout << "This is the first encryption half: " << half << endl;
		cout << "This is the second encryption half: " << otherHalf << endl;
		cout << "This is the post-encryption string" << xor (half, otherHalf) << endl;
	}
	return xor (half, otherHalf);
}
void maze() {
	Map m(12, 12);
	m.createWall(0, 0, 0, 11);
	m.createBorders();

	m.setCharAt('!', 3, 1);
	m.setCharAt('@', 3, 3);
	m.setCharAt('E', 9, 3);
	m.setCharDisplayText('!', "An arrow trap shot you in the head");
	m.registerCollectable('@', "Health Potion");
	m.registerCollectable('$', "Mana Potion");
	m.startMovement();
}
int main() {
	string procin;
	bool proc = false;
	cout << "Would you like to see the inner workings of this program? (YES or NO)" << endl;
	cin >> procin;
	if (procin == "YES") {
		proc = true;
		cout << "Now showing processes." << endl;
	}
	if (procin == "SKIP") {
		maze();
	}
	else {
		cout << "Process showing disabled" << endl;
	}
	unordered_map<string, string> um;
	ofstream outfile("login.txt", ios::app);
	ifstream infile("login.txt");
	string p;
	string u;
	while (infile >> p&&infile >> u) {
		um.insert({ p,u });
	}
	bool cchar = false;
	string username;
	string password;
	while (true) {
		char select;
		cout << "Login Program" << endl;
		cout << "1:Register" << endl;
		cout << "2:Login" << endl;
		cout << "3:Exit" << endl;
		cin >> select;
		if (select == '1') {
			while (cchar = false) {
				cout << "Username" << endl;
				cin >> username;
				if (username.length() >= 8) {
					cchar = true;
				}
				else {
					cout << "Your username must be at least 8 characters." << endl;
				}
			}
			cchar = false;
			while (cchar = false) {
				cout << "Password" << endl;
				cin >> password;
				if (password.length() >= 8) {
					cchar = true;
				}
				else {
					cout << "Your password must be at least 8 characters." << endl;
				}
			}
			um.insert({ enc(password, proc),username });
			outfile << enc(password, proc) << " " << username << endl;
		}
		else if (select == '2') {
			cout << "Username" << endl;
			string username;
			cin >> username;
			cout << "Password" << endl;
			string password;
			cin >> password;
			bool useexists = false;
			for (auto it = um.begin(); it != um.end(); ++it) {
				if (it->second == username) {
					useexists = true;
				}
			}
			if (um[enc(password, proc)] == username) {
				cout << "You successfully logged in." << endl;
				maze();
				return 0;
			}
			else if (useexists == true) {
				cout << "Incorrect password" << endl;
			}
			else {
				cout << "No such username in database" << endl;
			}
		}
		else if (select == '3') {
			return 0;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}