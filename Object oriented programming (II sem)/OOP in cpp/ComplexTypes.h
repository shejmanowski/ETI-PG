#pragma once
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<Windows.h>

#define EMPTY_FIELD '_'
#define CHAR_OFFSET 48
#define START_ORGANISMS_NUMBER 10

using namespace std;



enum class Direction { DIR_UP, DIR_RIGTH, DIR_DOWN, DIR_LEFT };

class Position {
	bool correct;
public:
	int x;
	int y;
	Position();
	Position(int x, int y);
	bool operator == (const Position& other);
	bool operator != (const Position& other);
	string toString() const;
	void setAsCorrect();
	void setAsIncorrect();
	bool isCorrect() const;
};
