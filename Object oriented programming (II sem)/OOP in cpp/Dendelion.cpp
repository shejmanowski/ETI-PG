#include"Dendelion.h"

Dendelion::Dendelion(Position pos, World& world) :
	Plant(DENDELION_NAME, DENDELION_STRENGTH, DENDELION_ICON, pos, world) {}

void Dendelion::action() {
	for (int i = 0; i < DENDELION_CHANCES_TO_SPREAD; i++) {
		if (world.chanceOfBeeingTrue(PLANT_SPREADING_CHANCE)) {
			spread();
		}
	}
}
