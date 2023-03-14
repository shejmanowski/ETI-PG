#pragma once
#include"Organism.h"
#include"Announcer.h"

class Organism;

class World {
private:
	int sizeX;
	int sizeY;
	int round;
	int playerCd;
	int abilityIsActive;
	int timeLeft;
	Organism*** board;
	vector<Organism*> livingOrganisms;
public:
	World(int sizeX, int sizeY);
	Organism*** getBoard();
	void generateWorld();
	Direction pickRandomDirection();
	bool fieldOutOfMap(Position pos);
	void drawWorld();
	void nextRound();
	bool isEmpty(Position pos);
	Position oneUnitInDirection(Position pos, Direction direction);
	void addToLivingOrganisms(Organism* organism);
	void updateBoard();
	void updateLivingOrganisms();
	void killOrganism(Organism* organism);
	void updateAgeForEveryOrganism();
	void setAbilityActive(bool isActive);
	void setTimeLeft(int timeLeft);
	void setAbilityCd(int cd);
	int getAbilityCd();
	int getTimeLeft();
	bool getAbilityActive();

	void createNewOrganism(char icon, Position pos);
	bool chanceOfBeeingTrue(float percent);
	Position pickRandomEmptyPosition();
	char pickOrganismIcon(int x);
	int getPlayerInput();
};
