#include"Animal.h"

Animal::Animal(string name, int strength, int initiative, char icon, Position pos, World& world)
	: Organism(name, strength, initiative, icon, pos, world) {
}
void Animal::action() {
	Position newPos = pickRandomNeighbourField(STANDARD_RANGE);
	if (world.isEmpty(newPos)) {
		move(newPos);
	}
	else {
		collision(world.getBoard()[newPos.x][newPos.y]);
	}
}
void Animal::collision(Organism* other) {
	Position posToMove(other->getPos());
	if (world.getBoard()[posToMove.x][posToMove.y]->getIcon() == icon) {			//there is the same species on the field
		reproduce();
	}
	else {																					//ther is different species on the field
		//if(other->getIcon() == )
		if (other->getIcon() == GUARANA_ICON) strength += 3;
		if (other->getIcon() == TURTLE_ICON && strength < 5) return;
		if (other->getIcon() == ANTYLOPE_ICON && world.chanceOfBeeingTrue(0.5f)) {
			Position emptyNeighbourField = other->findEmptyNeighbourField(other->getPos());
			if (emptyNeighbourField.isCorrect()) {
				other->move(emptyNeighbourField);
				move(posToMove);
			}			
		}
		if (strength >= other->getStrength()) {
			Announcer::addAnnounce(name + " ate " + other->getName());
			world.killOrganism(other);
			move(posToMove);
		}
		else {
			Announcer::addAnnounce(other->getName() + " killed " + name);
			world.killOrganism(this);
		}
	}
}
void Animal::move(Position pos) {
	position = pos;
}
void Animal::reproduce() {
	Position newAnimalPos = findEmptyNeighbourField(position);
	if (!newAnimalPos.isCorrect()) return;										//no place to put new animal
	Announcer::addAnnounce(name + " got reporduced");
	world.createNewOrganism(icon, newAnimalPos);
}
bool Animal::isStronger(Organism* other) {
	if (this->getStrength() > other->getStrength()) return true;
	else return false;
}
Animal::~Animal() {
}