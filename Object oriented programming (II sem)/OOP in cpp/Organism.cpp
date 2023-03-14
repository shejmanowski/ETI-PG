#include"Organism.h"

Organism::Organism(string name, int strength, int initiative, char icon, Position pos, World& world)
	: name(name), strength(strength), initiative(initiative), icon(icon), position(pos), world(world), age(0)
{

}

string Organism::getName() const {
	return name;
}
int Organism::getStrength() const {
	return strength;
}
int Organism::getInitiative() const {
	return initiative;
}
int Organism::getXPos() const {
	return position.x;
}
int Organism::getYPos() const {
	return position.y;
}
Position Organism::getPos() const {
	return position;
}
char Organism::getIcon() const {
	return icon;
}
World& Organism::getWorld() const {
	return world;
}

void Organism::setXPos(int x) {
	position.x = x;
}
void Organism::setYPos(int y) {
	position.y = y;
}
void Organism::setPos(int x, int y) {
	position.x = x;
	position.y = y;
}

Position Organism::pickRandomNeighbourField(int range) {
	Position newPos;
	do {
		newPos = position;
		Direction dir = world.pickRandomDirection();

		if (dir == Direction::DIR_UP) {
			newPos.y -= range;
		}
		else if (dir == Direction::DIR_RIGTH) {
			newPos.x += range;
		}
		else if (dir == Direction::DIR_DOWN) {
			newPos.y += range;
		}
		else if (dir == Direction::DIR_LEFT) {
			newPos.x -= range;
		}
	} while (world.fieldOutOfMap(newPos));

	return newPos;
}
Position Organism::findEmptyNeighbourField(Position startingPos) {
	Position emptyField;
	bool fieldFound = false;
	for (int i = 0; i < 4; i++) {
		emptyField = world.oneUnitInDirection(startingPos, (Direction)i);
		if (emptyField.isCorrect() && world.isEmpty(emptyField)) {
			fieldFound = true;
			break;
		}
	}
	if (!fieldFound) {
		emptyField.setAsIncorrect();
	}
	return emptyField;
}
string Organism::toString() {
	return name + position.toString();
}

void Organism::updateAge() {
	age++;
}

int Organism::getAge() const {
	return age;
}

Organism::~Organism() {
}
