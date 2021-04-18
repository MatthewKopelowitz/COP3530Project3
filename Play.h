#pragma once
#include <string>
using namespace std;

class Play {
public:
	long gameID = -1;
	string date = "";
	int quarter = -1;
	int minute = -1;
	int second = -1;
	string offenseTeam = "";
	string defenseTeam = "";
	int down = -1;
	int toGo = -1;
	int yardLine = -1;
	bool seriesFirstDown;
	int yardsGained ;
	string formation;
	bool isRush;
	bool isPass;
	bool isIncomplete;
	bool isTouchdown;
	bool isSack;
	bool isInterception;
	bool isFumble;
	bool isPenalty;
	bool isTwoPointConversion;
	bool isTwoPointConversionSuccessful;
	string penaltyTeam;
	int penaltyYards;

	Play() {}
};