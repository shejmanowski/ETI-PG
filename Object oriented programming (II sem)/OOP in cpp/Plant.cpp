#include"Plant.h"

Plant::Plant(string name, int strength, char icon, Position pos, World& world)
	: Organism(name, strength, PLANT_INITIATIVE, icon, pos, world) {
}

void Plant::action() {
	if (world.chanceOfBeeingTrue(PLANT_SPREADING_CHANCE)) {
		spread();
	}
}

void Plant::collision(Organism* other) {

}

void Plant::move(Position pos) {

}

void Plant::spread() {
	Position pos = findEmptyNeighbourField(position);
	if (pos.isCorrect()) {
		world.createNewOrganism(icon, pos);
		Announcer::addAnnounce(name + " spreaded");
	}
}

Plant::~Plant()
{
}