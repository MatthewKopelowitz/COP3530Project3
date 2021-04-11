#pragma once
#include "Game.h"

struct Team {
	string name;
    vector<Game> season18;
	vector<Game> season19;
	vector<Game> season20;

	Team(string name) {
	    this->name = name;
	}
};