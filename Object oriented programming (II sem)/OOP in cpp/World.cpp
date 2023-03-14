#include"World.h"
#include"AllOrganisms.h"

World::World(int sizeX, int sizeY)
	: sizeX(sizeX), sizeY(sizeY), round(0), board() {
	board = new Organism** [sizeX];
	for (int i = 0; i < sizeX; i++) {		
		board[i] = new Organism* [sizeY];
	}
	abilityIsActive = false;
	playerCd = 0;
	timeLeft = 0;
}

Direction World::pickRandomDirection() {
	int randomDir = rand() % 4;		//random numb between 0 and 3 - one for each direction
	return (Direction)randomDir;
}
Organism*** World::getBoard() {
	return board;
}
void World::generateWorld()
{
	for (int i = 0; i < START_ORGANISMS_NUMBER * 2; i++) {
		char icon = pickOrganismIcon(i % START_ORGANISMS_NUMBER);
		Position randomPos = pickRandomEmptyPosition();
		createNewOrganism(icon, randomPos);
		updateBoard();
	}
	Position randomPos = pickRandomEmptyPosition();
	createNewOrganism('X', randomPos);
	updateBoard();
}
bool World::fieldOutOfMap(Position pos) {
	if (pos.x < 0 || pos.x >= sizeX || pos.y < 0 || pos.y >= sizeY) return true;
	else return false;
}
void World::drawWorld() {
	system("CLS");
	cout << "SZYMON HEJMANOWSKI 184487" << endl;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (board[j][i] == nullptr) cout << EMPTY_FIELD;
			else cout << board[j][i]->getIcon();
		}
		cout << endl;
	}
	Announcer::printAnnounces();
}
void World::nextRound() {
	updateAgeForEveryOrganism();
	for (int i = 0; i < livingOrganisms.size(); i++) {
		if (livingOrganisms[i]->getAge() != 0) {
			livingOrganisms[i]->action();
			updateBoard();
		}
	}
	updateLivingOrganisms();
	drawWorld();
	Announcer::clear();
}
bool World::isEmpty(Position pos) {
	for (int i = 0; i < livingOrganisms.size(); i++) {
		if (livingOrganisms[i] != nullptr && pos == livingOrganisms[i]->getPos()) {
			return false;
		}
	}
	return true;
}
Position World::oneUnitInDirection(Position pos, Direction direction) {
	Position oneInDirection = pos;
	switch (direction) {
	case Direction::DIR_UP:
		oneInDirection.y--;
		break;
	case Direction::DIR_RIGTH:
		oneInDirection.x++;
		break;
	case Direction::DIR_DOWN:
		oneInDirection.y++;
		break;
	case Direction::DIR_LEFT:
		oneInDirection.x--;
		break;
	}
	if (fieldOutOfMap(oneInDirection)) {
		oneInDirection.setAsIncorrect();
	}
	return oneInDirection;
}
void World::addToLivingOrganisms(Organism* organism) {
	livingOrganisms.push_back(organism);
}
void World::updateBoard() {
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			board[i][j] = nullptr;
		}
	}
	for (int i = 0; i < livingOrganisms.size(); i++) {
		if (livingOrganisms[i] != nullptr) {
			Position organismPos = livingOrganisms[i]->getPos();
			board[organismPos.x][organismPos.y] = livingOrganisms[i];
		}
	}
}
void World::updateLivingOrganisms() {
	for (int i = 0; i < livingOrganisms.size(); i++) {
		if (livingOrganisms[i] == nullptr) livingOrganisms.erase(livingOrganisms.begin() + i);
	}
}
void World::killOrganism(Organism* organism) {
	for (int i = 0; i < livingOrganisms.size(); i++) {
		if (livingOrganisms[i] == organism) {
			livingOrganisms.erase(livingOrganisms.begin() + i);
			return;
		}
	}
}
void World::createNewOrganism(char icon, Position pos) {
	if (fieldOutOfMap(pos)) return;
	Organism* newOrganism = nullptr;
	switch (icon) {
	case WOLF_ICON:
		newOrganism = new Wolf(pos, *this);
		break;
	case SHEEP_ICON:
		newOrganism = new Sheep(pos, *this);
		break;
	case FOX_ICON:
		newOrganism = new Fox(pos, *this);
		break;
	case TURTLE_ICON:
		newOrganism = new Turtle(pos, *this);
		break;
	case ANTYLOPE_ICON:
		newOrganism = new Antylope(pos, *this);
		break;
	case GRASS_ICON:
		newOrganism = new Grass(pos, *this);
		break;
	case DENDELION_ICON:
		newOrganism = new Dendelion(pos, *this);
		break;
	case GUARANA_ICON:
		newOrganism = new Guarana(pos, *this);
		break;
	case WOLFBERRIES_ICON:
		newOrganism = new Wolfberries(pos, *this);
		break;
	case BORSCHT_ICON:
		newOrganism = new PineBorscht(pos, *this);
		break;
	case 'X':
		newOrganism = new Player(pos, *this);
		break;
	}
	if(newOrganism) addToLivingOrganisms(newOrganism);
}
bool World::chanceOfBeeingTrue(float percent) {
	int random = rand() % 100 + 1; //random between 1 and 100
	percent *= 100;
	if (random <= percent) return true;
	else return false;
}


void World::updateAgeForEveryOrganism() {
	for (int i = 0; i < livingOrganisms.size(); i++) {
		livingOrganisms[i]->updateAge();
	}
}
Position World::pickRandomEmptyPosition() {
	Position randPos;
	do {
		int randomX = rand() % sizeX;		//random numb between 0 and 3 - one for each direction
		int randomY = rand() % sizeY;
		randPos = { randomX, randomY };
	} while (fieldOutOfMap(randPos));
	randPos.setAsCorrect();
	return randPos;
}
char World::pickOrganismIcon(int x) {
	switch (x) {
	case 0:
		return WOLF_ICON;
	case 1:
		return SHEEP_ICON;
	case 2:
		return FOX_ICON;
	case 3:
		return TURTLE_ICON;
	case 4:
		return ANTYLOPE_ICON;
	case 5:
		return GRASS_ICON;
	case 6:
		return DENDELION_ICON;
	case 7:
		return GUARANA_ICON;
	case 8:
		return WOLFBERRIES_ICON;
	case 9:
		return BORSCHT_ICON;
	}
}
int World::getPlayerInput() {
	cout << endl << "Wpisz kierunek ruchu (wsad) i zaakceptuj enterem..." << endl;
	char input;
	if (cin >> input) {
		if (input == 'w') {
			return 0;
		}
		else if (input == 'd') {
			return 1;
		}
		else if (input == 's') {
			return 2;
		}
		else if (input == 'a') {
			return 3;
		}
		else if (input == 'q') {
			return 4;
		}
	}
}
void World::setAbilityActive(bool isActive) {
	abilityIsActive = isActive;
}
void World::setTimeLeft(int timeLeft) {
	this->timeLeft = timeLeft;
}
void World::setAbilityCd(int cd) {
	playerCd = cd;
}
int World::getAbilityCd() {
	return playerCd;
}
int World::getTimeLeft() {
	return timeLeft;
}
bool World::getAbilityActive() {
	return abilityIsActive;
}