#include"Announcer.h"

vector<string> Announcer::toAnnounce;

void Announcer::addAnnounce(string announce) {
	toAnnounce.push_back(announce);
}

void Announcer::printAnnounces() {
	cout << endl << "===============" << endl;
	for (int i = 0; i < toAnnounce.size(); i++) {
		cout << toAnnounce[i] << endl;
	}
	cout << "===============";
}

void Announcer::clear() {
	toAnnounce.clear();
}