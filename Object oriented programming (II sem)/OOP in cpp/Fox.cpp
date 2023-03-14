#include"Fox.h"

Fox::Fox(Position pos, World& world):
	Animal(FOX_NAME, FOX_STRENGTH, FOX_INITIATIVE, FOX_ICON, pos, world) {
}

void Fox::action() {
	Position newPos = pickRandomNeighbourField(STANDARD_RANGE);
	if (world.isEmpty(newPos)) {
		move(newPos);
	}
	else if (isStronger(world.getBoard()[newPos.x][newPos.y])) {
		collision(world.getBoard()[newPos.x][newPos.y]);
	}
	else return;
}