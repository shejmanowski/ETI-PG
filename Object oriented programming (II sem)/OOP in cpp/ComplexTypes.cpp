#include"ComplexTypes.h"

Position::Position() {
	this->x = 0;
	this->y = 0;
	correct = false;
}
Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
	this->correct = true;
}
bool Position::operator == (const Position& other) {
	if (this->x == other.x && this->y == other.y) {
		return true;
	}
	else return false;
}
bool Position::operator != (const Position& other) {
	if (this->x == other.x && this->y == other.y) {
		return false;
	}
	else return true;
}
string Position::toString() const {
	string ret = "";
	string toAdd = "(";
	ret = ret + toAdd;
	toAdd = x + CHAR_OFFSET;
	ret = ret + toAdd;
	toAdd = ", ";
	ret = ret + toAdd;
	toAdd = y + CHAR_OFFSET;
	ret = ret + toAdd;
	toAdd = ")";
	ret = ret + toAdd;
	return ret;
}

void Position::setAsCorrect() {
	correct = true;
}
void Position::setAsIncorrect() {
	correct = false;
}
bool Position::isCorrect() const {
	return correct;
}
