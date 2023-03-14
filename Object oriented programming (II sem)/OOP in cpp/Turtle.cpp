#include"Turtle.h"

Turtle::Turtle(Position pos, World& world) :
	Animal(TURTLE_NAME, TURTLE_STRENGTH, TURTLE_INITIATIVE, TURTLE_ICON, pos, world) {}

void Turtle::action() {
	if (world.chanceOfBeeingTrue(0.75f)) {
		return;
	}
	Position newPos = pickRandomNeighbourField(STANDARD_RANGE);
	if (world.isEmpty(newPos)) {
		move(newPos);
	}
	else {
		collision(world.getBoard()[newPos.x][newPos.y]);
	}
}

void Turtle::collision(Organism* other) {

}