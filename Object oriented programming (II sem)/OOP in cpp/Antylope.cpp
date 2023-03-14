#include"Antylope.h"

Antylope::Antylope(Position pos, World& world) :
	Animal(ANTYLOPE_NAME, ANTYLOPE_STRENGTH, ANTYLOPE_INITIATIVE, ANTYLOPE_ICON, pos, world) {
}

void Antylope::action() {
	Position newPos = pickRandomNeighbourField(ANTYLOPE_RANGE);
	if (world.isEmpty(newPos)) {
		move(newPos);
	}
	else {
		collision(world.getBoard()[newPos.x][newPos.y]);
	}
}

