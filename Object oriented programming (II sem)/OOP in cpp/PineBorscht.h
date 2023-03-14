#pragma once
#include"Plant.h"

class World;
class Plant;

class PineBorscht: public Plant {
public:
	PineBorscht(Position pos, World& world);

	void action() override;
};