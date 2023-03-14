#include"Player.h"

class World;

Player::Player(Position pos, World& world) :
	Animal(PLAYER_NAME, PLAYER_STRENGTH, PLAYER_INITIATIVE, PLAYER_ICON, pos, world) {
}

void Player::action() {
	Direction playerDir;
	int input = world.getPlayerInput();
	if (input == 4 && world.getAbilityCd() == 0) {
		world.setTimeLeft(5);
		world.setAbilityActive(true);
		playerDir = (Direction)world.getPlayerInput();
	}
	else playerDir = (Direction)input;
	Position newPos;
	newPos = world.oneUnitInDirection(position, playerDir);
	if (world.getAbilityActive() && world.getTimeLeft() > 2) {
		newPos = world.oneUnitInDirection(newPos, playerDir);
		world.setTimeLeft(world.getTimeLeft() - 1);
	}
	else if (world.getAbilityActive() && world.chanceOfBeeingTrue(0.5f)) {
		newPos = world.oneUnitInDirection(newPos, playerDir);
		world.setTimeLeft(world.getTimeLeft() - 1);
	}
	if (world.getTimeLeft() < 1) {
		world.setAbilityActive(false);
		world.setAbilityCd(5);
	}
	if (!newPos.isCorrect()) return;
	if (world.isEmpty(newPos)) {
		move(newPos);
	}
	else {
		collision(world.getBoard()[newPos.x][newPos.y]);
	}
}

void Player::collision(Organism* other) {
	Position posToMove(other->getPos());
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
		world.killOrganism(other);
		move(posToMove);
	}
	else {
		world.killOrganism(this);
	}
}