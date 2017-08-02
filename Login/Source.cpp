#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

int main() {
	while (true) {
		unordered_map<string, string> um;
		char select;
		cout << "Login Program" << endl;
		cout << "1:Register" << endl;
		cout << "2:Login" << endl;
		cout << "3:Exit" << endl;
		cin >> select;
		if (select == 1) {
			cout << "Username" << endl;
			string username;
			cin >> username;
			cout << "Password" << endl;
			string password;
			cin >> password;
			um.insert({ password,username });
		}
		else if (select == 2) {
			cout << "Username" << endl;
			string username;
			cin >> username;
			cout << "Password" << endl;
			string password;
			cin >> password;
			if (um[password] == username) {
				cout << "You successfully logged in." << endl;
				return 0;
			}
			else {
				cout << "Incorrect username or password" << endl;
			}
		}
		else if (select == 3) {
			return 0;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}