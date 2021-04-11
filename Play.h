#pragma once
#include <string>
using namespace std;

enum Formation {
	FIELDGOAL, NOHUDDLE, NOHUDDLESHOTGUN, PUNT, SHOTGUN, UNDERCENTER, WILDCAT
};

enum TeamName {
	PIT, LV, KC, BAL, ARI, LAC, SF, IND, SEA, DEN, CIN, CLE, MIA, LA, NYG, DAL, CAR, NO, NE, NYJ, MIN, CHI, WAS, TEN, ATL, TB, HOU, JAX, DET, GB, BUF, PHI
};

struct Play {
    long gameID;
    string date;
    int quarter;
    int minute;
    int second;
    TeamName offenseTeam;
    TeamName defenseTeam;
	int down;
	int toGo;
	int yardLine;
	bool seriesFirstDown;
	string description;
	int yards;
	Formation formation;
	bool isRush;
	bool isPass;
	bool isIncomplete;
	bool isTouchdown;
	bool isSack;
	bool isChallenge;
	bool isChallengeReversed;
	bool isMeasurement;
	bool isInterception;
	bool isFumble;
	bool isPenalty;
	bool isTwoPointConversion;
	bool isTwoPointConversionSuccessful;
	bool isPenaltyAccepted;
	TeamName penaltyTeam;
	bool isNoPlay;
	int penaltyYards;
};