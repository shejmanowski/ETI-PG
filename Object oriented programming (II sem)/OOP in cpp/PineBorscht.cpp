#include"PineBorscht.h"

PineBorscht::PineBorscht(Position pos, World& world) :
	Plant(BORSCHT_NAME, BORSCHT_STRENGTH, BORSCHT_ICON, pos, world) {}

void PineBorscht::action() {
	for (int i = 0; i < 4; i++) {
		Position posOfOrganismToKill = world.oneUnitInDirection(position, (Direction)i);
		if (posOfOrganismToKill.isCorrect()) {
			Organism* organismToKill = world.getBoard()[posOfOrganismToKill.x][posOfOrganismToKill.y];
			if (organismToKill != nullptr) {
				char icon = organismToKill->getIcon();
				if (icon == WOLF_ICON || icon == FOX_ICON || icon == SHEEP_ICON || icon == TURTLE_ICON || icon == ANTYLOPE_ICON) {
					world.killOrganism(organismToKill);
				}
			}
		}
	}
}