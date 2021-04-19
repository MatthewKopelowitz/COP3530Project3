#pragma once
#include <string>
#include <iostream>
using namespace std;

class Play {
public:
	long gameID = -1;
	string date = "";
	int monthInt = -1;
	int dayInt = -1;
	int yearInt = -1;
	int quarter = -1;
	int minute = -1;
	int second = -1;
	string secondStr = "";
	string offenseTeam = "";
	string defenseTeam = "";
	int down = -1;
	int toGo = -1;
	int yardLine = -1;
	bool seriesFirstDown = false;
	int yardsGained ;
	string formation;
	bool isRush;
	bool isPass;
	bool isIncomplete;
	bool isTouchdown = false;
	bool isSack;
	bool isInterception;
	bool isFumble;
	bool isPenalty;
	bool isTwoPointConversion;
	bool isTwoPointConversionSuccessful;
	string penaltyTeam;
	int penaltyYards;

	Play() {}

	void printData() const {
		cout << "GAME ID: " << gameID << endl;
		cout << "Play from game between " << offenseTeam << " (on the offensive) and " << defenseTeam << " (on the defensive) on " << date << ".\n";
		cout << "Down " << down << " with " << toGo << " yards to go in ";
		if (quarter >= 5) {
			cout << "OT";
		}
		else {
			cout << "quarter " << quarter;
		}
		cout << ", " << minute << ":";
		if (second < 10) {
			cout << "0";
			cout << second;
		}
		else {
			cout << second;
		}
		cout << " remaining.\n";
		cout << yardsGained << " yards gained after starting at the " << yardLine << " yard line!\n";
		if (isTouchdown) {
			cout << "TOUCHDOWN!\n";
		}
		else if (seriesFirstDown) {
			cout << "First Down!\n";
		}
		else {
			cout << "No first down.\n";
		}
		cout << "Formation : " << formation << endl;
		isPenalty ? cout << "PENALTY!\n" : cout << "No flag.\n";
		cout << endl;
	}
};