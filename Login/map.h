#pragma once

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <map>

using namespace std;


class Map {
public:
	Map(int numRows, int numCols); // NOTE: everything should be done with format [rows][cols]
	void createWall(int sr, int sc, int er, int ec); // creates a wall starting at point [sr][sc] to [er][ec]
													 // where sr=starting row, ec = ending column, etc.
	void print(); // prints the map starting with [0][0] at top left
	void createBorders(); // creates walls around the edge of the map
	void setPlayerPos(int row, int col); // sets the position of the player where r=rows, c=cols to be shown next map update
	void setPlayerChar(char c); // sets character to represent player
	void setEndChar(char c); // sets character to represent endpoint
	void setCharAt(char c, int row, int col); // sets the char at location [row][col] to c
	void startMovement(); // starts game
	int getpr(); // gets player row
	int getpc(); // gets player col
	void setCharDisplayText(char c, string text); // makes it so text displays when you go over char c
	void setEndTextCheck(vector<string>& words);
	void endCheck();
	void registerCollectable(char c, string name);
	int getCollectable(string name);


private:
	// player's position (initialized to [1][1])
	int pr;
	int pc;

	// map characters
	char wallChar; // initialized to (char)177
	char playerChar; // initialized to 'P'
	char endChar; // initialized to 'E'

	map<char, string> charDisplayMap;
	string displayText;

	char prevChar;

	vector<string> endTextCheck;

	// these are for collectibles
	vector<char> colChar;
	vector<string> colName;
	vector<int> colInventory;

	// map
	vector<vector<char> > map;


};

#endif