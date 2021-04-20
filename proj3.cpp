#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
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

//removes front spaces from the str argument (used for loading data)
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
        teams[newPlay.defenseTeam].defensivePlays.push_back(newPlay); //add to correct vector

        linesPassed++;
    }

    stream.close();

}

//ENUM LIST OF RANKING TYPES
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

//COMPARATORS AND FUNCTIONS FOR USE IN HEAP AND BUBBLE
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

bool getMostYardsFunc(Play p1, Play p2) {
    return (p1.yardsGained < p2.yardsGained);
}

bool getLeastYardsFunc(Play p1, Play p2) {
    return (p1.yardsGained > p2.yardsGained);
}

bool getEarliestInGameFunc(Play p1, Play p2) {
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

bool getLatestInGameFunc(Play p1, Play p2) {
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

bool getEarliestGameDateFunc(Play p1, Play p2) {
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

bool getLatestGameDateFunc(Play p1, Play p2) {
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

bool getMostYardsToGoFunc(Play p1, Play p2) {
    return (p1.toGo < p2.toGo);
}

bool getLeastYardsToGoFunc(Play p1, Play p2) {
    return (p1.toGo > p2.toGo);
}

bool getMostYardsToTDFunc(Play p1, Play p2) {
    return (p1.yardLine > p2.yardLine);
}

bool getLeastYardsToTDFunc(Play p1, Play p2) {
    return (p1.yardLine < p2.yardLine);
}


//STRATIFYING FUNCTION
vector<Play> stratify (
    const unordered_map<string, Team>& teams,
    const unordered_map<string, bool>& offTeam,
    const unordered_map<string, bool>& defTeam,
    const unordered_map<int, bool>& quarter,
    bool onlyFirstDowns, bool onlyTouchdowns) 
{
    vector<Play> result;
    for (auto iter = teams.begin(); iter != teams.end(); iter++) {
        if (offTeam.at(iter->first)) {
            for (Play p : iter->second.offensivePlays) {
                bool getsAdded = true;
                if(!defTeam.at(p.defenseTeam))
                    getsAdded = false;
                if (!quarter.at(p.quarter))
                    getsAdded = false;
                if (p.isTouchdown != onlyTouchdowns || p.seriesFirstDown != onlyFirstDowns)
                    getsAdded = false;
                if(getsAdded)
                    result.push_back(p); //if it passes all conditions, add to stratified vector
            }
        }
    }
    return result;
}

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
    if (numToDisplay > filteredPlays.size())
        numToDisplay = filteredPlays.size();
    //cout << "about to compare values\n";
    switch (cv) { //REPLACE EACH FOR LOOP TO ONLY PUSH FROM FILTEREDPLAYS
    case mostYards:
        //cout << "mostyards\n";
        for (Play p : filteredPlays) {
            PQ_mostYards.push(p);
        }
        //cout << "all pushed\n";
        for (int i = 0; i < numToDisplay; i++) {
            //cout << "current i:" << i << endl;
            result.push_back(PQ_mostYards.top());
            PQ_mostYards.pop();
        }
        //cout << "about to return\n";
        break;
    case leastYards:
        //cout << "leastyards\n";
        for (Play p : filteredPlays) {
            PQ_leastYards.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYards.top());
            PQ_leastYards.pop();
        }
        break;
    case earliestInGame:
        //cout << "earlyingame\n";
        for (Play p : filteredPlays) {
            PQ_earliestInGame.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_earliestInGame.top());
            PQ_earliestInGame.pop();
        }
        break;
    case latestInGame:
        //cout << "lateingame\n";
        for (Play p : filteredPlays) {
            PQ_latestInGame.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_latestInGame.top());
            PQ_latestInGame.pop();
        }
        break;
    case earliestGameDate:
        //cout << "earlydate\n";
        for (Play p : filteredPlays) {
            PQ_earliestGameDate.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_earliestGameDate.top());
            PQ_earliestGameDate.pop();
        }
        break;
    case latestGameDate:
        //cout << "latedate\n";
        for (Play p : filteredPlays) {
            PQ_latestGameDate.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_latestGameDate.top());
            PQ_latestGameDate.pop();
        }
        break;
    case mostYardsToGo:
        //cout << "mostyardstogo\n";
        for (Play p : filteredPlays) {
            PQ_mostYardsToGo.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_mostYardsToGo.top());
            PQ_mostYardsToGo.pop();
        }
        break;
    case leastYardsToGo:
        //cout << "leastyardstogo\n";
        for (Play p : filteredPlays) {
            PQ_leastYardsToGo.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYardsToGo.top());
            PQ_leastYardsToGo.pop();
        }
        break;
    case mostYardsToTD:
        //cout << "mostyardstoTD\n";
        for (Play p : filteredPlays) {
            PQ_mostYardsToTD.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_mostYardsToTD.top());
            PQ_mostYardsToTD.pop();
        }
        break;
    case leastYardsToTD:
        //cout << "leastyardstoTD\n";
        for (Play p : filteredPlays) {
            PQ_leastYardsToTD.push(p);
        }
        for (int i = 0; i < numToDisplay; i++) {
            result.push_back(PQ_leastYardsToTD.top());
            PQ_leastYardsToTD.pop();
        }
        break;
    default:
        //cout << "heapsort error\n";
        break;
    }
    //cout << "heapsort done\n";
    return result;
}

//Sorting functions
vector<Play> bubbleSort(comparedValue comp, int numToDisplay, vector<Play>& inputVec) {
    //NEEDS SOME SORT OF INPUT THAT SAYS WHAT FUNCTION TO SORT BY
    if (numToDisplay > inputVec.size())
        numToDisplay = inputVec.size();
    for (int i = 0; i < inputVec.size() - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < inputVec.size() - i - 1; j++) {
            bool compVal;
            switch (comp) {
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
                compVal = getEarliestGameDateFunc(inputVec[j], inputVec[j + 1]);
                break;
            case latestGameDate:
                compVal = getLatestGameDateFunc(inputVec[j], inputVec[j + 1]);
                break;
            case mostYardsToGo:
                compVal = getMostYardsToGoFunc(inputVec[j], inputVec[j + 1]);
                break;
            case leastYardsToGo:
                compVal = getLeastYardsToGoFunc(inputVec[j], inputVec[j + 1]);
                break;
            case mostYardsToTD:
                compVal = getMostYardsToTDFunc(inputVec[j], inputVec[j + 1]);
                break;
            case leastYardsToTD:
                compVal = getLeastYardsToTDFunc(inputVec[j], inputVec[j + 1]);
                break;
            }
            if (!compVal) { //had to flip this so it would do it properly
                Play temp = inputVec[j];
                inputVec[j] = inputVec[j + 1];
                inputVec[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }

    vector<Play> outputVec;
    for (int i = 0; i < numToDisplay; i++) {
        outputVec.push_back(inputVec[inputVec.size() - 1 - i]);
    }

    return outputVec;
}

////TO OUTPUT THE TOP X NUM OF PLAYS FROM THE SORTED VECTOR
//void printTopXPlays(int numPlays, const vector<Play>& sortedPlays) {
//    for (int i = 0; i < numPlays; i++) {
//        sortedPlays[i].printData();
//    }
//}

int main(int argc, char* argv[]) {
    //creating the data map to keep track of team-stratified "play" lists
    unordered_map<string, Team> teams;
    createTeams(teams);

    //initializing the clock (in microseconds)
    using chrono::duration_cast;
    using chrono::microseconds;
    typedef chrono::high_resolution_clock clock;
    //cout << "about to parse arguments\n";
    int season = stoi(argv[1]); //decides what data sets to load
    unsigned long long offensiveTeams = stoull(argv[2]); //correlates to un_map<string, bool>
    unsigned long long defensiveTeams = stoull(argv[3]); //correlates to un_map<string, bool>
    int rankVal = stoi(argv[4]); //DECIDES ENUM THAT GOES TO SORT FUNCTIONS
    int quarter = stoi(argv[5]); //correlates to un_map<int,bool>
    bool firstDown = stoi(argv[6]) == 1; //is true if only first down plays are allowed
    bool scoreTD = stoi(argv[7]) == 1; //is true if only touchdown plays are allowed
    int numPlays = stoi(argv[8]); //GOES STRAIGHT TO SECOND ARG OF SORT FUNCTIONS
   
    if (scoreTD)
        firstDown = true; //otherwise it prints nothing

    bool s2018 = (season & 1) != 0;
    bool s2019 = (season & 2) != 0; //bitwise selection
    bool s2020 = (season & 4) != 0;

    if (s2018) //load proper data
        loadData("2018_prog_cleaned", teams);
    if (s2019)
        loadData("2019_prog_cleaned", teams);
    if (s2020)
        loadData("2020_prog_cleaned", teams);

    unordered_map<string, bool> useTeamO;
    {
        useTeamO["ARI"] = ((offensiveTeams & 1) != 0);
        useTeamO["ATL"] = ((offensiveTeams & 2) != 0);
        useTeamO["BUF"] = ((offensiveTeams & 4) != 0);
        useTeamO["BAL"] = ((offensiveTeams & 8) != 0);
        useTeamO["CAR"] = ((offensiveTeams & 16) != 0);
        useTeamO["CIN"] = ((offensiveTeams & 32) != 0);
        useTeamO["CLE"] = ((offensiveTeams & 64) != 0);
        useTeamO["CHI"] = ((offensiveTeams & 128) != 0);
        useTeamO["DAL"] = ((offensiveTeams & 256) != 0);
        useTeamO["DEN"] = ((offensiveTeams & 512) != 0);
        useTeamO["DET"] = ((offensiveTeams & 1024) != 0);
        useTeamO["GB"] =  ((offensiveTeams & 2048) != 0);
        useTeamO["HOU"] = ((offensiveTeams & 4096) != 0);
        useTeamO["IND"] = ((offensiveTeams & 8192) != 0); //bit selection as opposed to trying to send in a ton of separate arguments - not perfect/clean but it works
        useTeamO["KC"] =  ((offensiveTeams & 16384) != 0);
        useTeamO["LV"] =  ((offensiveTeams & 32768) != 0);
        useTeamO["LAC"] = ((offensiveTeams & 65536) != 0);
        useTeamO["LA"] = ((offensiveTeams & 131072) != 0);
        useTeamO["JAX"] = ((offensiveTeams & 262144) != 0);
        useTeamO["MIA"] = ((offensiveTeams & 524288) != 0);
        useTeamO["MIN"] = ((offensiveTeams & 1048576) != 0);
        useTeamO["NE"] =  ((offensiveTeams & 2097152) != 0);
        useTeamO["NO"] =  ((offensiveTeams & 4194304) != 0);
        useTeamO["NYG"] = ((offensiveTeams & 8388608) != 0);
        useTeamO["NYJ"] = ((offensiveTeams & 16777216) != 0);
        useTeamO["PHI"] = ((offensiveTeams & 33554432) != 0);
        useTeamO["SF"] =  ((offensiveTeams & 67108864) != 0);
        useTeamO["SEA"] = ((offensiveTeams & 134217728) != 0);
        useTeamO["PIT"] = ((offensiveTeams & 268435456) != 0);
        useTeamO["TB"] =  ((offensiveTeams & 536870912) != 0);
        useTeamO["TEN"] = ((offensiveTeams & 1073741824) != 0);
        useTeamO["WAS"] = ((offensiveTeams & 2147483648) != 0);
    }
    unordered_map<string, bool> useTeamD;
    {
        useTeamD["ARI"] = ((defensiveTeams & 1) != 0);
        useTeamD["ATL"] = ((defensiveTeams & 2) != 0);
        useTeamD["BUF"] = ((defensiveTeams & 4) != 0);
        useTeamD["BAL"] = ((defensiveTeams & 8) != 0);
        useTeamD["CAR"] = ((defensiveTeams & 16) != 0);
        useTeamD["CIN"] = ((defensiveTeams & 32) != 0);
        useTeamD["CLE"] = ((defensiveTeams & 64) != 0);
        useTeamD["CHI"] = ((defensiveTeams & 128) != 0);
        useTeamD["DAL"] = ((defensiveTeams & 256) != 0);
        useTeamD["DEN"] = ((defensiveTeams & 512) != 0);
        useTeamD["DET"] = ((defensiveTeams & 1024) != 0);
        useTeamD["GB"] =  ((defensiveTeams & 2048) != 0);
        useTeamD["HOU"] = ((defensiveTeams & 4096) != 0);
        useTeamD["IND"] = ((defensiveTeams & 8192) != 0); //bit selection as opposed to trying to send in a ton of separate arguments - not perfect/clean but it works
        useTeamD["KC"] =  ((defensiveTeams & 16384) != 0);
        useTeamD["LV"] =  ((defensiveTeams & 32768) != 0);
        useTeamD["LAC"] = ((defensiveTeams & 65536) != 0);
        useTeamD["LA"] = ((defensiveTeams & 131072) != 0);
        useTeamD["JAX"] = ((defensiveTeams & 262144) != 0);
        useTeamD["MIA"] = ((defensiveTeams & 524288) != 0);
        useTeamD["MIN"] = ((defensiveTeams & 1048576) != 0);
        useTeamD["NE"] =  ((defensiveTeams & 2097152) != 0);
        useTeamD["NO"] =  ((defensiveTeams & 4194304) != 0);
        useTeamD["NYG"] = ((defensiveTeams & 8388608) != 0);
        useTeamD["NYJ"] = ((defensiveTeams & 16777216) != 0);
        useTeamD["PHI"] = ((defensiveTeams & 33554432) != 0);
        useTeamD["SF"] =  ((defensiveTeams & 67108864) != 0);
        useTeamD["SEA"] = ((defensiveTeams & 134217728) != 0);
        useTeamD["PIT"] = ((defensiveTeams & 268435456) != 0);
        useTeamD["TB"] =  ((defensiveTeams & 536870912) != 0);
        useTeamD["TEN"] = ((defensiveTeams & 1073741824) != 0);
        useTeamD["WAS"] = ((defensiveTeams & 2147483648) != 0);
    }
    comparedValue sortVal;
    {
        switch (rankVal) {
        case 1:
            sortVal = mostYards;
            break;
        case 2:
            sortVal = leastYards;
            break;
        case 4:
            sortVal = earliestInGame;
            break;
        case 8:
            sortVal = latestInGame;
            break;
        case 16:
            sortVal = earliestGameDate; //switch for passing into functions
            break;
        case 32:
            sortVal = latestGameDate;
            break;
        case 64:
            sortVal = mostYardsToGo;
            break;
        case 128:
            sortVal = leastYardsToGo;
            break;
        case 256:
            sortVal = mostYardsToTD;
            break;
        case 512:
            sortVal = leastYardsToTD;
            break;
        default:
            cout << "ERROR BAD RANKVAL\n";
            return 0;
        }
    }
    unordered_map<int, bool> useQ;
    {
        useQ[1] = ((quarter & 1) != 0);
        useQ[2] = ((quarter & 2) != 0);
        useQ[3] = ((quarter & 4) != 0); //another bit selection
        useQ[4] = ((quarter & 8) != 0);
        useQ[5] = ((quarter & 16) != 0);
    }
    //cout << "passed input filtering, time to stratify\n";
    vector<Play> filteredPlays = stratify(teams, useTeamO, useTeamD, useQ, firstDown, scoreTD);
    //cout << "stratify passed\n";
    if (filteredPlays.size() == 0) {
        cout << "Unable to find any plays that meet those requirements. Please try again.\n";
        cout << "Make sure that if you select only 1 team for offense and defense that they are different\n"; //error messages
        return 0;
    }
    //cout << "size check donw\n";
    auto heapStart = clock::now();
    vector<Play> sortedV = heapSort(sortVal, numPlays, filteredPlays);
    auto heapFinish = clock::now();
    //cout << "heapsort passed\n";
    if (numPlays > sortedV.size())
        cout << "Not enough plays to display " << numPlays << " plays, but these meet your requirements:\n\n"; //making sure it can print them all
    for (Play p : sortedV) {
        p.printData();
    }
    std::cout << "\nHeap Sort cost : " << duration_cast<microseconds>(heapFinish - heapStart).count() << " microseconds." << endl << endl << endl;

    auto bubbleStart = clock::now();
    vector<Play> sortedVB = bubbleSort(sortVal, numPlays, filteredPlays);
    auto bubbleFinish = clock::now();
    //cout << "bubblesort passed\n";
    for (Play p : sortedVB) {
        p.printData();
    }
    std::cout << "\nBubble Sort cost : " << duration_cast<microseconds>(bubbleFinish - bubbleStart).count() << " microseconds." << endl;



    return 0;
}
