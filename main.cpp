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
        if (c < (48 + lowestChoice) || c > (48 + highestChoice)) {
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

//Sorting functions
/*
vector<Team> bubbleSort(sortType type, const unordered_map<string, Team>& teams) {
    //must be implemented with a comparison function depending on the sortType
    vector<Team> v;
    for (auto it = teams.begin(); it != teams.end(); it++) {
        v.push_back(it->second);
    }
    for (int i = 0; i < teams.size()-1; i++) {
        for (int j = 0; j < teams.size()-i-1; j++) {
            if (type ==  && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            } else if (type == && v[j] > v[j+1]) {
                Team temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    return v;
}
*/

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

//TO OUTPUT THE TOP X NUM OF PLAYS FROM THE SORTED VECTOR
void printTopXPlays(int numPlays, const vector<Play>& sortedPlays) {
    for (int i = 0; i < numPlays; i++) {
        sortedPlays[i].printData();
    }
}

int main() {
    //creating the data map to keep track of team-stratified "play" lists
    unordered_map<string, Team> teams;
    createTeams(teams);

    //initializing the clock (in microseconds)
    using chrono::duration_cast;
    using chrono::microseconds;
    typedef chrono::high_resolution_clock clock;

    //loading the data in from untagged CSV files
    auto start = clock::now();
    loadData("2018_prog_cleaned", teams);
    loadData("2019_prog_cleaned", teams);
    loadData("2020_prog_cleaned", teams);
    auto end = clock::now();
    std::cout << "Data input cost : " << duration_cast<microseconds>(end - start).count() << " microseconds." << endl;

    ////asks the user if they want to see stats for a single team or for top ten teams and records input in isSingleTeam boolean
    //string menuChoice;
    //int int_MC = 0;
    //*cin >> menuChoice;
    //int int_MC = stoi(menuChoice);
    //switch (int_MC) {
    //    case 1:
    //        isSingleTeam = true;
    //        break;
    //    case 2:
    //        isSingleTeam = false;
    //        break;
    //}*/

    ////simple unordered map just to keep track of which seasons the user selects to show stats for
    //unordered_map<string, bool> sznSelect;
    //sznSelect["2018"] = false;
    //sznSelect["2019"] = false;
    //sznSelect["2020"] = false;

    //cout << "\nMENU OPTIONS" << endl;
    //cout << "1. 2018 Season" << endl;
    //cout << "2. 2019 Season" << endl;
    //cout << "3. 2020 Season" << endl;
    //cout << "4. 2018-2019 Seasons" << endl;
    //cout << "5. 2019-2020 Seasons" << endl;
    //cout << "6. 2018-2020 Seasons" << endl;
    //cout << "Please input a number: ";

    //cin >> menuChoice;
    //while (!isValid(menuChoice, 1, 6)) {
    //    cout << "Please re-enter a valid menu choice ('1' through '6'): ";
    //    cin >> menuChoice;
    //}
    //int_MC = stoi(menuChoice);

    ////asks the user which season(s) they want to see stats for and stores their input as booleans in the unordered_map sznSelect
    //switch (int_MC) {
    //    case 1:
    //        sznSelect["2018"] = true;
    //        break;
    //    case 2:
    //        sznSelect["2019"] = true;
    //        break;
    //    case 3:
    //        sznSelect["2020"] = true;
    //        break;
    //    case 4:
    //        sznSelect["2018"] = true;
    //        sznSelect["2019"] = true;
    //        break;
    //    case 5:
    //        sznSelect["2019"] = true;
    //        sznSelect["2020"] = true;
    //        break;
    //    case 6:
    //        sznSelect["2018"] = true;
    //        sznSelect["2019"] = true;
    //        sznSelect["2020"] = true;
    //        break;
    //}

    //cout << "\nMENU OPTIONS" << endl;
    //cout << "Which statistic would you like to see?" << endl;
    //cout << "1. Number of games won by majority plays being running vs passing" << endl;
    //cout << "2. First down completion success rate on running vs passing plays" << endl;
    //cout << "3. Average yards gained on running vs passing plays" << endl;
    //cout << "4. Chance of any play gaining 30+ yards for running vs passing" << endl;
    //cout << "5. Chance of any play being a turnover for running vs passing" << endl;
    //cout << "6. Average yards gained in shotgun formation vs other formations" << endl;
    //cout << "7. Chance of penalty on offense vs defense on running vs passing play" << endl;
    //cout << "Please input a number" << endl;

    //cin >> menuChoice;
    //while (!isValid(menuChoice,1,7)) {
    //    cout << "Please re-enter a valid menu choice ('1' through '7'): ";
    //    cin >> menuChoice;
    //}
    //int_MC = stoi(menuChoice);

    ////switch between sorting according to which stat the user selected
    //vector<Team> sortedTeams;
    //*switch (int_MC) {
    //default case:
    //    break;
    //case 1:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 2:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 3:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 4:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 5:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 6:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //case 7:
    //    sortedTeams = bubbleSort();
    //    sortedTeams = heapSort();
    //    break;
    //    
    //}
    //*/


    std::cout << endl << endl;
    vector<Play> samplePlayList = teams["MIA"].offensivePlays;
    auto heapStart = clock::now();
    vector<Play> sortedV = heapSort(mostYardsToTD, 15, samplePlayList);
    auto heapFinish = clock::now();
    for (Play p : sortedV) {
        p.printData();
    }
    std::cout << "\nHeap Sort cost : " << duration_cast<microseconds>(heapFinish - heapStart).count() << " microseconds." << endl;


    return 0;
}