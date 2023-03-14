#pragma once
#include"Plant.h"

class World;
class Plant;

class Guarana : public Plant {
public:
	Guarana(Position pos, World& world);
};