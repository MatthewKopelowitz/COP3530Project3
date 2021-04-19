#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <cmath>
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

//ensures the input is only a numeric entry of length 1
bool isValid(string str, int lowestChoice, int highestChoice) {
    if (str.length() > 1) {
        return false;
    }
    for (char c : str) {
        if (c < (48 + lowestChoice) || c >(48 + highestChoice)) {
            return false;
        }
    }
    return true;
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

//loads a data set
void loadData(const string& fileName, unordered_map<string, Team>& teams) {
    ifstream stream;
    stream.open(fileName);
    long int linesPassed = 0;
    string trashStringVal;

    while (true) {
        string line;
        Play newPlay = Play();

        getline(stream, line, ',');
        if (line == "") {
            break;
        }
        newPlay.gameID = stoi(line);

        //TAKING IN THE DATE AS A STRING AND 3 SEPARATE INTS
        string monthS, dayS, yearS;
        getline(stream, monthS, '/');
        newPlay.monthInt = stoi(monthS);
        getline(stream, dayS, '/');
        newPlay.dayInt = stoi(dayS);
        getline(stream, yearS, ',');
        newPlay.yearInt = stoi(yearS);   //NEW
        newPlay.date = to_string(newPlay.monthInt) + "/"
            + to_string(newPlay.dayInt) + "/"
            + to_string(newPlay.yearInt);

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

        getline(stream, line, ','); //FIRST DOWN (TRASH)

        getline(stream, line, ',');
        newPlay.yardsGained = stoi(line);
        if (newPlay.yardsGained >= newPlay.toGo) {
            newPlay.seriesFirstDown = true;
        }
        if (newPlay.yardsGained + newPlay.yardLine >= 100) {
            newPlay.isTouchdown = true;
        } // NEW

        getline(stream, line, ',');
        line = removeFrontSpaces(line);
        newPlay.formation = line;

        getline(stream, line, ',');
        newPlay.isRush = stoi(line);

        getline(stream, line, ',');
        newPlay.isPass = stoi(line);

        getline(stream, line, ',');
        newPlay.isIncomplete = stoi(line);

        getline(stream, line, ',');//IS TOUCHDOWN (TRASH)

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



enum comparedValue {
    mostYards, //the play with the most yards gained
    leastYards, //the play with the least (or most negative) yards gained 
    earliestInGame, //the play that happens earliest in a game (closest to starting kickoff)
    latestInGame, //the play that happens latest in a game (closest to final time)
    earliestGameDate, //play that occured least recently
    latestGameDate, //play that occured most recently
    mostYardsToGo, //play that had the most yards togo (pre-hike)
    leastYardsToGo, //play that had the least yards togo (pre-hike)
    mostYardsToTD, //play that started most yards away from the opp's endzone
    leastYardsToTD //play that started least yards away from the opp's endzone
};

struct getMostYards {
    bool operator()(Play p1, Play p2) {
        return (p1.yardsGained < p2.yardsGained);
    }
};
struct getLeastYards {
    bool operator()(Play p1, Play p2) {
        return (p1.yardsGained > p2.yardsGained);
    }
};
struct getEarliestInGame {
    bool operator()(Play p1, Play p2) {
        if (p1.quarter > p2.quarter) {
            return true;
        }
        else if (p1.quarter < p2.quarter) {
            return false;
        }
        else {
            if (p1.minute < p2.minute) {
                return true;
            }
            else if (p1.minute > p2.minute) {
                return false;
            }
            else {
                if (p1.second < p2.second) {
                    return true;
                }
                else
                    return false;
            }
        }
    }
};
struct getLatestInGame {
    bool operator()(Play p1, Play p2) {
        if (p1.quarter < p2.quarter) {
            return true;
        }
        else if (p1.quarter > p2.quarter) {
            return false;
        }
        else {
            if (p1.minute > p2.minute) {
                return true;
            }
            else if (p1.minute < p2.minute) {
                return false;
            }
            else {
                if (p1.second > p2.second) {
                    return true;
                }
                else
                    return false;
            }
        }
    }
};
struct getEarliestGameDate {
    bool operator()(Play p1, Play p2) {
        if (p1.yearInt > p2.yearInt) {
            return true;
        }
        else if (p1.yearInt < p2.yearInt) {
            return false;
        }
        else {
            if (p1.monthInt > p2.monthInt) {
                return true;
            }
            else if (p1.monthInt < p2.monthInt) {
                return false;
            }
            else {
                if (p1.dayInt > p2.dayInt) {
                    return true;
                }
                else if (p1.dayInt < p2.dayInt) {
                    return false;
                }
                else {
                    getEarliestInGame obj;
                    return obj(p1, p2);
                }
            }
        }
    }
};
struct getLatestGameDate {
    bool operator()(Play p1, Play p2) {
        if (p1.yearInt < p2.yearInt) {
            return true;
        }
        else if (p1.yearInt > p2.yearInt) {
            return false;
        }
        else {
            if (p1.monthInt < p2.monthInt) {
                return true;
            }
            else if (p1.monthInt > p2.monthInt) {
                return false;
            }
            else {
                if (p1.dayInt < p2.dayInt) {
                    return true;
                }
                else if (p1.dayInt > p2.dayInt) {
                    return false;
                }
                else {
                    getLatestInGame obj;
                    return obj(p1, p2);
                }
            }
        }
    }
};
struct getMostYardsToGo {
    bool operator()(Play p1, Play p2) {
        return (p1.toGo < p2.toGo);
    }
};
struct getLeastYardsToGo {
    bool operator()(Play p1, Play p2) {
        return (p1.toGo > p2.toGo);
    }
};
struct getMostYardsToTD {
    bool operator()(Play p1, Play p2) {
        return (p1.yardLine > p2.yardLine);
    }
};
struct getLeastYardsToTD {
    bool operator()(Play p1, Play p2) {
        return (p1.yardLine < p2.yardLine);
    }
};

//CHANGE TO
//OUTPUT PLAYS VECTOR
//TAKE IN A FILTEREDPLAYS VECTOR
//void heapSort(comparedValue cv, const unordered_map<string, Team>& filteredPlays) {
//    //initializing a priority queue of each type of comparator (we will decide which to use in the next branch)
//    priority_queue <Play, vector<Play>, getMostYards> PQ_mostYards;
//    priority_queue <Play, vector<Play>, getLeastYards> PQ_leastYards;
//    priority_queue <Play, vector<Play>, getEarliestInGame> PQ_earliestInGame;
//    priority_queue <Play, vector<Play>, getLatestInGame> PQ_latestInGame;
//    priority_queue <Play, vector<Play>, getEarliestGameDate> PQ_earliestGameDate;
//    priority_queue <Play, vector<Play>, getLatestGameDate> PQ_latestGameDate;
//    priority_queue <Play, vector<Play>, getMostYardsToGo> PQ_mostYardsToGo;
//    priority_queue <Play, vector<Play>, getLeastYardsToGo> PQ_leastYardsToGo;
//    priority_queue <Play, vector<Play>, getMostYardsToTD> PQ_mostYardsToTD;
//    priority_queue <Play, vector<Play>, getLeastYardsToTD> PQ_leastYardsToTD;
//
//
//    switch (cv) { //REPLACE EACH FOR LOOP TO ONLY PUSH FROM FILTEREDPLAYS
//    case mostYards:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_mostYards.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_mostYards.top().printData();
//            PQ_mostYards.pop();
//        }
//        break;
//    case leastYards:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_leastYards.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_leastYards.top().printData();
//            PQ_leastYards.pop();
//        }
//        break;
//    case earliestInGame:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_earliestInGame.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_earliestInGame.top().printData();
//            PQ_earliestInGame.pop();
//        }
//        break;
//    case latestInGame:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_latestInGame.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_latestInGame.top().printData();
//            PQ_latestInGame.pop();
//        }
//        break;
//    case earliestGameDate:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_earliestGameDate.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_earliestGameDate.top().printData();
//            PQ_earliestGameDate.pop();
//        }
//        break;
//    case latestGameDate:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_latestGameDate.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_latestGameDate.top().printData();
//            PQ_latestGameDate.pop();
//        }
//        break;
//    case mostYardsToGo:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_mostYardsToGo.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_mostYardsToGo.top().printData();
//            PQ_mostYardsToGo.pop();
//        }
//        break;
//    case leastYardsToGo:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_leastYardsToGo.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_leastYardsToGo.top().printData();
//            PQ_leastYardsToGo.pop();
//        }
//        break;
//    case mostYardsToTD:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_mostYardsToTD.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_mostYardsToTD.top().printData();
//            PQ_mostYardsToTD.pop();
//        }
//        break;
//    case leastYardsToTD:
//        for (auto iter = filteredPlays.begin(); iter != filteredPlays.end(); iter++) {
//            for (Play p : iter->second.offensivePlays) {
//                PQ_leastYardsToTD.push(p);
//            }
//        }
//        for (int i = 0; i < 10; i++) {
//            PQ_leastYardsToTD.top().printData();
//            PQ_leastYardsToTD.pop();
//        }
//        break;
//    }
//
//}

//NEW HEAP SORT FUNCTION
vector<Play> heapSort(comparedValue cv, int numToDisplay, const vector<Play>& filteredPlays) {
    //initializing a priority queue of each type of comparator (we will decide which to use in the next branch)
    priority_queue <Play, vector<Play>, getMostYards> PQ_mostYards;
    priority_queue <Play, vector<Play>, getLeastYards> PQ_leastYards;
    priority_queue <Play, vector<Play>, getEarliestInGame> PQ_earliestInGame;
    priority_queue <Play, vector<Play>, getLatestInGame> PQ_latestInGame;
    priority_queue <Play, vector<Play>, getEarliestGameDate> PQ_earliestGameDate;
    priority_queue <Play, vector<Play>, getLatestGameDate> PQ_latestGameDate;
    priority_queue <Play, vector<Play>, getMostYardsToGo> PQ_mostYardsToGo;
    priority_queue <Play, vector<Play>, getLeastYardsToGo> PQ_leastYardsToGo;
    priority_queue <Play, vector<Play>, getMostYardsToTD> PQ_mostYardsToTD;
    priority_queue <Play, vector<Play>, getLeastYardsToTD> PQ_leastYardsToTD;
    vector<Play> result;


    switch (cv) { //REPLACE EACH FOR LOOP TO ONLY PUSH FROM FILTEREDPLAYS
    case mostYards:
        for (Play p : filteredPlays) {
            PQ_mostYards.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_mostYards.top());
            PQ_mostYards.pop();
        }
        break;
    case leastYards:
        for (Play p : filteredPlays) {
            PQ_leastYards.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYards.top());
            PQ_leastYards.pop();
        }
        break;
    case earliestInGame:
        for (Play p : filteredPlays) {
            PQ_earliestInGame.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_earliestInGame.top());
            PQ_earliestInGame.pop();
        }
        break;
    case latestInGame:
        for (Play p : filteredPlays) {
            PQ_latestInGame.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_latestInGame.top());
            PQ_latestInGame.pop();
        }
        break;
    case earliestGameDate:
        for (Play p : filteredPlays) {
            PQ_earliestGameDate.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_earliestGameDate.top());
            PQ_earliestGameDate.pop();
        }
        break;
    case latestGameDate:
        for (Play p : filteredPlays) {
            PQ_latestGameDate.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_latestGameDate.top());
            PQ_latestGameDate.pop();
        }
        break;
    case mostYardsToGo:
        for (Play p : filteredPlays) {
            PQ_mostYardsToGo.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_mostYardsToGo.top());
            PQ_mostYardsToGo.pop();
        }
        break;
    case leastYardsToGo:
        for (Play p : filteredPlays) {
            PQ_leastYardsToGo.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYardsToGo.top());
            PQ_leastYardsToGo.pop();
        }
        break;
    case mostYardsToTD:
        for (Play p : filteredPlays) {
            PQ_mostYardsToTD.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_mostYardsToTD.top());
            PQ_mostYardsToTD.pop();
        }
        break;
    case leastYardsToTD:
        for (Play p : filteredPlays) {
            PQ_leastYardsToTD.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYardsToTD.top());
            PQ_leastYardsToTD.pop();
        }
        break;
    }

    return result;
}

//Sorting functions
vector<Play> bubbleSort(comparedValue comp, vector<Play>& inputVec) {
    //NEEDS SOME SORT OF INPUT THAT SAYS WHAT FUNCTION TO SORT BY
    for (int i = 0; i < inputVec.size() - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < inputVec.size() - i - 1; j++) {
            bool compVal;
            switch(comp){
            case mostYards:
                compVal = getMostYardsFunc(inputVec[j], inputVec[j + 1]);
                break;
            case leastYards:
                compVal = getLeastYardsFunc(inputVec[j], inputVec[j + 1]);
                break;
            case earliestInGame:
                compVal = getEarliestInGameFunc(inputVec[j], inputVec[j + 1]);
                break;
            case latestInGame:
                compVal = getLatestInGameFunc(inputVec[j], inputVec[j + 1]);
                break;
            case earliestGameDate:
                break;
            case latestGameDate:
                break;
            case mostYardsToGo:
                break;
            case leastYardsToGo:
                break;
            }
            if (compVal) { //COMPARATOR FUNCTION HERE
                Play temp = inputVec[j];
                inputVec[j] = inputVec[j + 1];
                inputVec[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }

    return inputVec;
}


//TO OUTPUT THE TOP X NUM OF PLAYS FROM THE SORTED VECTOR
void printTopXPlays(int numPlays, const vector<Play>& sortedPlays) {
    for (int i = 0; i < numPlays; i++) {
        sortedPlays[i].printData();
    }
}

int main(int argc, char* argv[]) {
    //creating the data map to keep track of team-stratified "play" lists
    unordered_map<string, Team> teams;
    createTeams(teams);

    //initializing the clock (in microseconds)
    using chrono::duration_cast;
    using chrono::microseconds;
    typedef chrono::high_resolution_clock clock;

    //loading the data in from untagged CSV files
    auto start = clock::now();
    //loadData("2018_prog_cleaned", teams);
    //loadData("2019_prog_cleaned", teams);
    //loadData("2020_prog_cleaned", teams);
    auto end = clock::now();
    //std::cout << "Data input cost : " << duration_cast<microseconds>(end - start).count() << " microseconds." << endl << endl << endl; //REMOVE ME PLEASE

    int season = stoi(argv[1]);
    unsigned long long offensiveTeams = stoull(argv[2]);
    unsigned long long defensiveTeams = stoull(argv[3]);
    int rankVal = stoi(argv[4]);
    int quarter = stoi(argv[5]);
    bool firstDown = stoi(argv[6]) == 1;
    bool scoreTD = stoi(argv[7]) == 1;
    int numPlays = stoi(argv[8]);

    bool s2018 = (season & 1) != 0;
    bool s2019 = (season & 2) != 0;
    bool s2020 = (season & 4) != 0;

    if(s2018)
        loadData("2018_prog_cleaned.csv", teams);
    if(s2019)
        loadData("2019_prog_cleaned.csv", teams);
    if(s2020)
        loadData("2020_prog_cleaned.csv", teams);
    
    unordered_map<string, bool> useTeamO;
    {
        if ((offensiveTeams & 1) != 0)
            useTeamO["ARI"] = true;
        if ((offensiveTeams & 2) != 0)
            useTeamO["ATL"] = true;
        if ((offensiveTeams & 4) != 0)
            useTeamO["BUF"] = true;
        if ((offensiveTeams & 8) != 0)
            useTeamO["BAL"] = true;
        if ((offensiveTeams & 16) != 0)
            useTeamO["CAR"] = true;
        if ((offensiveTeams & 32) != 0)
            useTeamO["CIN"] = true;
        if ((offensiveTeams & 64) != 0)
            useTeamO["CLE"] = true;
        if ((offensiveTeams & 128) != 0)
            useTeamO["CHI"] = true;
        if ((offensiveTeams & 256) != 0)
            useTeamO["DAL"] = true;
        if ((offensiveTeams & 512) != 0)
            useTeamO["DEN"] = true;
        if ((offensiveTeams & 1024) != 0)
            useTeamO["DET"] = true;
        if ((offensiveTeams & 2048) != 0)
            useTeamO["GB"] = true;
        if ((offensiveTeams & 4096) != 0)
            useTeamO["HOU"] = true;
        if ((offensiveTeams & 8192) != 0)
            useTeamO["IND"] = true;
        if ((offensiveTeams & 16384) != 0)
            useTeamO["KC"] = true;
        if ((offensiveTeams & 32768) != 0)
            useTeamO["LV"] = true;
        if ((offensiveTeams & 65536) != 0)
            useTeamO["LAC"] = true;
        if ((offensiveTeams & 131072) != 0)
            useTeamO["LAR"] = true;
        if ((offensiveTeams & 262144) != 0)
            useTeamO["JAX"] = true;
        if ((offensiveTeams & 524288) != 0)
            useTeamO["MIA"] = true;
        if ((offensiveTeams & 1048576) != 0)
            useTeamO["MIN"] = true;
        if ((offensiveTeams & 2097152) != 0)
            useTeamO["NE"] = true;
        if ((offensiveTeams & 4194304) != 0)
            useTeamO["NO"] = true;
        if ((offensiveTeams & 8388608) != 0)
            useTeamO["NYG"] = true;
        if ((offensiveTeams & 16777216) != 0)
            useTeamO["NYJ"] = true;
        if ((offensiveTeams & 33554432) != 0)
            useTeamO["PHI"] = true;
        if ((offensiveTeams & 67108864) != 0)
            useTeamO["SF"] = true;
        if ((offensiveTeams & 134217728) != 0)
            useTeamO["SEA"] = true;
        if ((offensiveTeams & 268435456) != 0)
            useTeamO["PIT"] = true;
        if ((offensiveTeams & 536870912) != 0)
            useTeamO["TB"] = true;
        if ((offensiveTeams & 1073741824) != 0)
            useTeamO["TEN"] = true;
        if ((offensiveTeams & 2147483648) != 0)
            useTeamO["WAS"] = true;
    }
    {
        unordered_map<string, bool> useTeamD;
        if ((defensiveTeams & 1) != 0)
            useTeamD["ARI"] = true;
        if ((defensiveTeams & 2) != 0)
            useTeamD["ATL"] = true;
        if ((defensiveTeams & 4) != 0)
            useTeamD["BUF"] = true;
        if ((defensiveTeams & 8) != 0)
            useTeamD["BAL"] = true;
        if ((defensiveTeams & 16) != 0)
            useTeamD["CAR"] = true;
        if ((defensiveTeams & 32) != 0)
            useTeamD["CIN"] = true;
        if ((defensiveTeams & 64) != 0)
            useTeamD["CLE"] = true;
        if ((defensiveTeams & 128) != 0)
            useTeamD["CHI"] = true;
        if ((defensiveTeams & 256) != 0)
            useTeamD["DAL"] = true;
        if ((defensiveTeams & 512) != 0)
            useTeamD["DEN"] = true;
        if ((defensiveTeams & 1024) != 0)
            useTeamD["DET"] = true;
        if ((defensiveTeams & 2048) != 0)
            useTeamD["GB"] = true;
        if ((defensiveTeams & 4096) != 0)
            useTeamD["HOU"] = true;
        if ((defensiveTeams & 8192) != 0)
            useTeamD["IND"] = true;
        if ((defensiveTeams & 16384) != 0)
            useTeamD["KC"] = true;
        if ((defensiveTeams & 32768) != 0)
            useTeamD["LV"] = true;
        if ((defensiveTeams & 65536) != 0)
            useTeamD["LAC"] = true;
        if ((defensiveTeams & 131072) != 0)
            useTeamD["LAR"] = true;
        if ((defensiveTeams & 262144) != 0)
            useTeamD["JAX"] = true;
        if ((defensiveTeams & 524288) != 0)
            useTeamD["MIA"] = true;
        if ((defensiveTeams & 1048576) != 0)
            useTeamD["MIN"] = true;
        if ((defensiveTeams & 2097152) != 0)
            useTeamD["NE"] = true;
        if ((defensiveTeams & 4194304) != 0)
            useTeamD["NO"] = true;
        if ((defensiveTeams & 8388608) != 0)
            useTeamD["NYG"] = true;
        if ((defensiveTeams & 16777216) != 0)
            useTeamD["NYJ"] = true;
        if ((defensiveTeams & 33554432) != 0)
            useTeamD["PHI"] = true;
        if ((defensiveTeams & 67108864) != 0)
            useTeamD["SF"] = true;
        if ((defensiveTeams & 134217728) != 0)
            useTeamD["SEA"] = true;
        if ((defensiveTeams & 268435456) != 0)
            useTeamD["PIT"] = true;
        if ((defensiveTeams & 536870912) != 0)
            useTeamD["TB"] = true;
        if ((defensiveTeams & 1073741824) != 0)
            useTeamD["TEN"] = true;
        if ((defensiveTeams & 2147483648) != 0)
            useTeamD["WAS"] = true;
    }
    {
        comparedValue sortVal;
        cout << (int)log2(rankVal) << endl;
        switch ((int)log2(rankVal)) {
        case 0:
            sortVal = mostYards;
            break;
        case 1:
            sortVal = leastYards;
            break;
        case 2:
            sortVal = earliestInGame;
            break;
        case 3:
            sortVal = latestInGame;
            break;
        case 4:
            sortVal = earliestGameDate;
            break;
        case 5:
            sortVal = latestGameDate;
            break;
        case 6:
            sortVal = mostYardsToGo;
            break;
        case 7:
            sortVal = leastYardsToGo;
            break;
        case 8:
            sortVal = mostYardsToTD;
            break;
        case 9:
            sortVal = leastYardsToTD;
            break;
        }
    }
    unordered_map<int, bool> useQ;
    if ((quarter & 1) != 0)
        useQ[1] = true;
    if ((quarter & 2) != 0)
        useQ[2] = true;
    if ((quarter & 4) != 0)
        useQ[3] = true;
    if ((quarter & 8) != 0)
        useQ[4] = true;
    if ((quarter & 16) != 0)
        useQ[5] = true;

    //int count = 0;
    //for (auto ite = useTeamO.begin(); ite != useTeamO.end(); ite++)
    //    if (ite->second)
    //        count++;
    //cout << "useTeamO count: " << count << endl;
    //count = 0;
    //for (auto ite = useTeamD.begin(); ite != useTeamD.end(); ite++)
    //    if (ite->second)
    //        count++;
    //cout << "useTeamD count: " << count << endl;
    //count = 0;
    //for (auto ite = useQ.begin(); ite != useQ.end(); ite++)
    //    if (ite->second)
    //        count++;
    //cout << "useQ count: " << count << endl;
    //if (firstDown)
    //    cout << "firstDown\n";
    //if (scoreTD)
    //    cout << "scoreTD\n" << endl;
    //cout << "numplays: " << numPlays << endl;

    /* mostYards, leastYards, earliestInGame, latestInGame, earliestGameDate, latestGameDate, mostYardsToGo, leastYardsToGo
    vector<Play> samplePlayList = teams["MIA"].offensivePlays;
    auto heapStart = clock::now();
    vector<Play> sortedV = heapSort(mostYards, 10, samplePlayList);
    auto heapFinish = clock::now();
    for (Play p : sortedV) {
        p.printData();
    }
    std::cout << "\nHeap Sort cost : " << duration_cast<microseconds>(heapFinish - heapStart).count() << " microseconds." << endl;

    */
    return 0;
}