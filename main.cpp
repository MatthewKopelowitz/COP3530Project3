#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "Team.h"
using namespace std;

//creates the 32 teams and adds them to the map
void createTeams(unordered_map<string, Team>& teams) {
    teams["PIT"] = Team("PIT");
    teams["LV"] = Team("LV");
    teams["KC"] = Team("KC");
    teams["BAL"] = Team("BAL");
    teams["ARI"] = Team("ARI");
    teams["LAC"] = Team("LAC");
    teams["SF"] = Team("SF");
    teams["IND"] = Team("IND");
    teams["SEA"] = Team("SEA");
    teams["DEN"] = Team("DEN");
    teams["CIN"] = Team("CIN");
    teams["CLE"] = Team("CLE");
    teams["MIA"] = Team("MIA");
    teams["LA"] = Team("LA");
    teams["NYG"] = Team("NYG");
    teams["DAL"] = Team("DAL");
    teams["CAR"] = Team("CAR");
    teams["NO"] = Team("NO");
    teams["NE"] = Team("NE");
    teams["NYJ"] = Team("NYJ");
    teams["MIN"] = Team("MIN");
    teams["CHI"] = Team("CHI");
    teams["WAS"] = Team("WAS");
    teams["TEN"] = Team("TEN");
    teams["ATL"] = Team("ATL");
    teams["TB"] = Team("TB");
    teams["HOU"] = Team("HOU");
    teams["JAX"] = Team("JAX");
    teams["DET"] = Team("DET");
    teams["GB"] = Team("GB");
    teams["BUF"] = Team("BUF");
    teams["PHI"] = Team("PHI");
}

//set isOK flag to false in case the string is empty
bool isNotEmpty(string str) {
    if (str.length() == 0)
        return false;
    else 
        return true;
}

//ensures the input is only a numeric entry
bool isValid(string str) {
    //returns false if has any non-int chars
}

//removes front spaces from the str argument
string removeFrontSpaces(string str) {
    int i = 0;
    if (str == "") {
        return "";
    }
    while (str[i] != ' ') {
        i++;
    }
    return str.erase(i, 1);
}

enum sortType {
    EarliestGame, LatestGame
};

//loads a data set
void loadData(const string& fileName, unordered_map<string, Team>& teams) {
    ifstream stream;
    stream.open(fileName);
    long int linesPassed = 0;
    string trashStringVal;

    getline(stream, trashStringVal, '\n');

    while (true) {
        string line;
        Play newPlay = Play();

        getline(stream, line, ',');
        if (line == "") {
            break;
        }
        newPlay.gameID = stoi(line);
        
        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.date = line;

        getline(stream, line, ',');
        newPlay.quarter = stoi(line);

        getline(stream, line, ',');
        newPlay.minute = stoi(line);

        getline(stream, line, ',');
        newPlay.second = stoi(line);

        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.offenseTeam = line;

        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.defenseTeam = line;

        getline(stream, line, ',');
        newPlay.down = stoi(line);

        getline(stream, line, ',');
        newPlay.toGo = stoi(line);

        getline(stream, line, ',');
        newPlay.yardLine = stoi(line);

        getline(stream, line, ',');
        newPlay.seriesFirstDown = stoi(line);

        getline(stream, line, ',');
        newPlay.yardsGained = stoi(line);

        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.formation = line;

        getline(stream, line, ',');
        newPlay.isRush = stoi(line);

        getline(stream, line, ',');
        newPlay.isPass = stoi(line);

        getline(stream, line, ',');
        newPlay.isIncomplete = stoi(line);

        getline(stream, line, ',');
        newPlay.isTouchdown = stoi(line);

        getline(stream, line, ',');
        newPlay.isSack = stoi(line);
        
        getline(stream, line, ',');
        newPlay.isInterception = stoi(line);

        getline(stream, line, ',');
        newPlay.isFumble = stoi(line);

        getline(stream, line, ',');
        newPlay.isPenalty = stoi(line);

        getline(stream, line, ',');
        newPlay.isTwoPointConversion = stoi(line);

        getline(stream, line, ',');
        newPlay.isTwoPointConversionSuccessful = stoi(line);

        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.penaltyTeam = line;

        getline(stream, line, '\n');
        newPlay.penaltyYards = stoi(line);

        teams[newPlay.offenseTeam].offensivePlays.push_back(newPlay);
        teams[newPlay.defenseTeam].defensivePlays.push_back(newPlay);
        
        linesPassed++;
    }

    cout << "lines passed : " << linesPassed << endl;

    stream.close();

}

//Sorting functions
void bubbleSort(sortType type, const unordered_map<string, Team>& teams) {
    //must be implemented with a comparison function depending on the sortType
}
void heapSort(sortType type, const unordered_map<string, Team>& teams) {
    //must be implemented with a comparison function depending on the sortType
}


int main() {
    //creating the data map to keep track of team-stratified "play" lists
    unordered_map<string, Team> teams;
    createTeams(teams);

    //initializing the clock
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    typedef std::chrono::high_resolution_clock clock;

    //loading the data in from untagged CSV files
    auto start = clock::now();
    loadData("2018_prog_cleaned", teams);
    loadData("2019_prog_cleaned", teams);
    loadData("2020_prog_cleaned", teams);
    auto end = clock::now();
    cout << duration_cast<microseconds>(end - start).count() << "microseconds" << endl;

    //VERY SIMPLE AND LIMITED GUI
    string menuChoice;
    int int_MC = 0;
    cout << "MENU OPTIONS" << endl;

    cin >> menuChoice;
    int_MC = stoi(menuChoice);

    switch (int_MC) {
    /*case 1:
        bubbleSort();
        heapSort();
    case 2:
        bubbleSort();
        heapSort();
    case 3:
        bubbleSort();
        heapSort();
    case 4:
        bubbleSort();
        heapSort();
    case 5:
        bubbleSort();
        heapSort();
        */
    }
    
    return 0;
}