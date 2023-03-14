#pragma once
#include"Plant.h"

class World;
class Plant;

class Wolfberries: public Plant {
public:
	Wolfberries(Position pos, World& world);
};