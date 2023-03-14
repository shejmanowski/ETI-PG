#pragma once
#include"World.h"

class Announcer {
protected:
	static vector<string> toAnnounce;
public:
	static void addAnnounce(string announce);
	static void printAnnounces();
	static void clear();
};