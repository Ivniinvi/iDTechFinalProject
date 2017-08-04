#include "map.h"

Map::Map(int numRows, int numCols) {
	for (int i = 0; i < numRows; i++) {
		vector<char> next;
		map.push_back(next);
		for (int j = 0; j < numCols; j++) {
			map[i].push_back(' ');
		}
	}

	wallChar = (char)177;
	playerChar = 'P';
	endChar = 'E';
	pr = 1;
	pc = 1;
	map[1][1] = playerChar;
	displayText = "";
	prevChar = ' ';
}

void Map::createWall(int sr, int sc, int er, int ec) {
	int temp;
	if (sr > er) { // switch if aren't in right order
		temp = er;
		er = sr;
		sr = temp;
	}
	if (sc > ec) {
		temp = sc;
		sc = ec;
		ec = temp;
	}
	bool canCreateWall = true;
	if (sr < 0 || sr >= map.size()) {
		cout << "first argument, starting row, must be in the range [0, " << map.size() - 1 << "]" << endl;
		canCreateWall = false;
	}
	if (sc < 0 || sc >= map[0].size()) {
		cout << "second argument, starting column, must be in the range [0, " << map[1].size() - 1 << "]" << endl;
		canCreateWall = false;
	}
	if (er < 0 || er >= map.size()) {
		cout << "third argument, end row, must be in the range [0, " << map.size() - 1 << "]" << endl;
		canCreateWall = false;
	}
	if (ec < 0 || ec >= map[0].size()) {
		cout << "fourth argument, end column, must be in the range [0, " << map[1].size() - 1 << "]" << endl;
		canCreateWall = false;
	}

	if (canCreateWall) {
		for (int i = sr; i <= er; i++) {
			for (int j = sc; j <= ec; j++) {
				map[i][j] = wallChar;
			}
		}
	}

}

void Map::print() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			cout << map[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < colChar.size(); i++) {
		cout << colChar[i] << " " << colName[i] << ": " << colInventory[i] << endl;
	}

	cout << endl << displayText << endl;


}

void Map::createBorders() {
	/*for (int i = 0; i < map.size(); i++) {
	map[i][0] = wallChar;
	map[i][map[0].size()-1] = wallChar;
	}
	for (int j = 0; j < map[0].size(); j++) {
	map[0][j] = wallChar;
	map[map.size() - 1][j];
	}*/
	createWall(0, 0, map.size() - 1, 0);
	createWall(0, 0, 0, map[0].size() - 1);
	createWall(map.size() - 1, 0, map.size() - 1, map[0].size() - 1);
	createWall(0, map[0].size() - 1, map.size() - 1, map[0].size() - 1);
}

void Map::setPlayerChar(char c) {
	playerChar = c;
}

void Map::setPlayerPos(int row, int col) {
	pr = row;
	pc = col;
}

void Map::setEndChar(char c) {
	endChar = c;
}

void Map::setCharAt(char c, int row, int col) {
	map[row][col] = c;
}

void Map::startMovement() {
	while (true) {
		system("cls");
		print();
		char input = getch();
		int nextpr = pr;
		int nextpc = pc;

		if (input == 'w') {
			nextpr -= 1;
		}
		else if (input == 'a') {
			nextpc -= 1;
		}
		else if (input == 's') {
			nextpr += 1;
		}
		else if (input == 'd') {
			nextpc += 1;
		}

		if (nextpr < 0 || nextpr >= map.size() || nextpc < 0 || nextpc >= map[0].size()) {
			continue; // tried to move out of bounds
		}
		else if (map[nextpr][nextpc] == ' ') {
			map[pr][pc] = prevChar;
			prevChar = ' ';
			pr = nextpr;
			pc = nextpc;
			map[pr][pc] = playerChar;
			displayText = "";
		}
		else if (map[nextpr][nextpc] == endChar) {
			endCheck();
		}
		else {
			for (auto it = charDisplayMap.begin(); it != charDisplayMap.end(); ++it) {
				if (map[nextpr][nextpc] == it->first) {
					map[pr][pc] = prevChar;
					displayText = it->second;
					prevChar = it->first;
					pr = nextpr;
					pc = nextpc;
					map[pr][pc] = playerChar;
				}
			}
			for (int i = 0; i < colChar.size(); i++) {
				if (map[nextpr][nextpc] == colChar[i]) {
					colInventory[i]++;
					map[pr][pc] = prevChar;
					displayText = "You got a " + colName[i];
					prevChar = ' ';
					pr = nextpr;
					pc = nextpc;
					map[pr][pc] = playerChar;
				}
			}
		}
	}
}

int Map::getpr() {
	return pr;
}

int Map::getpc() {
	return pc;
}

void Map::setCharDisplayText(char c, string text) {
	charDisplayMap.insert({ c, text });
}

void Map::setEndTextCheck(vector<string>& words) {
	endTextCheck = words;
}

void Map::endCheck() {
	system("color 40");
	int demonhealth = 100;
	int playerhealth = 100;
	int energy = 0;
	int mana = 20;
	cout << "You have entered combat with the Demon General, Anthalon" << endl;
	cout << "If his energy reaches 100%, he will annihilate the dungeon and everything in it" << endl;
	while (demonhealth > 0) {
		char select;
		cout << "Your health: " << playerhealth << endl;
		cout << "Your mana: " << mana << endl;
		cout << "Anthalon's health: " << demonhealth << endl;
		cout << "Anthalon's energy: " << energy << endl;
		cout << "1:Items" << endl;
		cout << "2:Combat" << endl;
		bool action = false;
		cin >> select;
		int hpcount = getCollectable("Health Potion");
		int mpcount = getCollectable("Mana Potion");
		if (select == '1') {
			if (hpcount > 0) {
				cout << "1:Health Potions: " << hpcount << endl;
			}

			cout << "3:Exit" << endl;
			char selec2;
			cin >> selec2;
			if (selec2 == '1') {
				if (hpcount > 0) {
					playerhealth = playerhealth + 30;
					action = true;
					if (playerhealth > 100) {
						playerhealth = 100;
					}
				}
				else {
					cout << "Not enough health potions" << endl;
				}
			}
			if (selec2 == '2') {
				if (mpcount > 0) {
					mana = mana + 15;
					action = true;
					if (mana > 20) {
						mana = 20;
					}
				}
				else {
					cout << "Not enough mana potions" << endl;
				}
			}
		}
		if (select == '2') {
			if (mana > 5) {
				cout << "1: Fireball" << endl;;
			}
			cout << "2: Sword Strike" << endl;
			cout << "3: Exit" << endl;
			char comselect;
			cin >> comselect;
			if (comselect == '1') {
				if (mana > 5) {
					int firedamage;
					firedamage = 16 + (rand() % static_cast<int>(24 - 16 + 1));
					mana = mana - 6;
					cout << "Your Fireball did " << firedamage << " damage to Anthalon." << endl;
					demonhealth = demonhealth - firedamage;
					action = true;
				}
			}
			if (comselect == '2') {
				int sworddamage;
				sworddamage = 12 + (rand() % static_cast<int>(17 - 12 + 1));
				demonhealth = demonhealth - sworddamage;
				cout << "Your Sword Strike did " << sworddamage << " damage to Anthalon" << endl;
				action = true;
			}
		}
		if (action == true) {
			int demonact;
			demonact = 1 + (rand() % static_cast<int>(2 - 1 + 1));
			if (demonact == 1) {
				cout << "Anthalon did 20 damage to you" << endl;
				cout << "Anthalon gained 15 energy" << endl;
				energy = energy + 15;
				playerhealth = playerhealth - 20;
			}
			if (demonact == 2) {
				cout << "Anthalon did 25 damage to you" << endl;
				cout << "Anthalon gained 10 energy" << endl;
				energy = energy + 10;
				playerhealth = playerhealth - 25;
			}
			if (energy > 99) {
				cout << "Anthalon unleashes the power of his fully charged doomsday weapon" << endl;
				cout << "Anthalon did a million damage to you, your children, and your children's children" << endl;
				playerhealth = playerhealth - 1000000;
			}
			if (playerhealth < 0) {
				cout << "You died. Horribly." << endl;
				while (true) {
					system("color 19");
					system("color 21");
					system("color 32");
					system("color 43");
					system("color 54");
					system("color 65");
					system("color 76");
					system("color 87");
					system("color 98");
				}
			}
		}
	}
}

void Map::registerCollectable(char c, string name) {
	colChar.push_back(c);
	colName.push_back(name);
	colInventory.push_back(0);
}

int Map::getCollectable(string name) {
	for (int i = 0; i < colName.size(); i++) {
		if (name == colName[i]) {
			return colInventory[i];
		}
	}
}