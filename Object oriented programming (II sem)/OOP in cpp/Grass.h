#pragma once
#include"Plant.h"

class World;
class Plant;

class Grass : public Plant {
public:
	Grass(Position pos, World& world);
};