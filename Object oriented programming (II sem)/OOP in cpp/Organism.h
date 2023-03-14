#pragma once
#include"ComplexTypes.h"
#include"OrganismsConstants.h"
#include"World.h"

class World;

class Organism {
protected:
	const string name;
	int strength;
	const int initiative;
	const char icon;
	int age;
	Position position;
	World& world;

public:	
	Organism(string name, int strength, int initiative, char icon, Position pos, World& world);
	string getName() const;
	int getStrength() const;
	int getInitiative() const;
	int getXPos() const;
	int getYPos() const;
	Position getPos() const;
	char getIcon() const;
	World& getWorld() const;
	int getAge() const;

	void setXPos(int x);
	void setYPos(int y);
	void setPos(int x, int y);
	Position pickRandomNeighbourField(int range);
	virtual Position findEmptyNeighbourField(Position startingPos);
	string toString();
	void updateAge();

	virtual void action() = 0;
	virtual void collision(Organism* other) = 0;
	virtual void move(Position pos) = 0;

	virtual ~Organism();
};