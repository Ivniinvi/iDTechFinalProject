#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <bitset>
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
string enc(string inp) {
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
	return xor (half, otherHalf);
}
int main() {
	unordered_map<string, string> um;
	ofstream outfile("login.txt", ios::app);
	ifstream infile("login.txt");
	string p;
	string u;
	while (infile >> p&&infile >> u) {
		um.insert({ p,u });
	}
	while (true) {
		char select;
		cout << "Login Program" << endl;
		cout << "1:Register" << endl;
		cout << "2:Login" << endl;
		cout << "3:Exit" << endl;
		cin >> select;
		if (select == '1') {
			cout << "Username" << endl;
			string username;
			cin >> username;
			cout << "Password" << endl;
			string password;
			cin >> password;
			um.insert({ enc(password),username });
			outfile << enc(password) << " " << username << endl;
		}
		else if (select == '2') {
			cout << "Username" << endl;
			string username;
			cin >> username;
			cout << "Password" << endl;
			string password;
			cin >> password;
			if (um[enc(password)] == username) {
				cout << "You successfully logged in." << endl;
				return 0;
			}
			else {
				cout << "Incorrect username or password" << endl;
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