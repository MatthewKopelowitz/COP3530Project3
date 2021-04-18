#pragma once
#include <vector>
#include "Play.h"

class Team {
public:
	string name = "";
	vector<Play> offensivePlays;
	vector<Play> defensivePlays;

	Team(string name) {
		this->name = name;
	}

	Team() {}
};