#include <iostream>
#include <fstream>
#include <unordered_map>
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

//convert a string to a formation enum
Formation stoF(const string& str) {
    Formation f;
    if (str == "FIELDGOAL") {
        f = FIELDGOAL;
    } else if (str == "NOHUDDLE") {
        f = NOHUDDLE;
    } else if (str == "NOHUDDLESHOTGUN") {
        f = NOHUDDLESHOTGUN;
    } else if (str == "PUNT") {
        f = PUNT;
    } else if (str == "SHOTGUN") {
        f = SHOTGUN;
    } else if (str == "UNDERCENTER") {
        f = UNDERCENTER;
    } else if (str == "WILDCAT") {
        f = WILDCAT;
    }
    return f;
}

//convert a string into a teamName enum
TeamName stoTN(const string& str) {
    TeamName t;
    if (str == "PIT") {
        t = PIT;
    } else if (str == "LV") {
        t = LV;
    } else if (str == "KC") {
        t = KC;
    } else if (str == "BAL") {
        t = BAL;
    } else if (str == "ARI") {
        t = ARI;
    } else if (str == "LAC") {
        t = LAC;
    } else if (str == "SF") {
        t = SF;
    }else if (str == "IND") {
        t = IND;
    } else if (str == "SEA") {
        t = SEA;
    } else if (str == "DEN") {
        t = DEN;
    } else if (str == "CIN") {
        t = CIN;
    } else if (str == "CLE") {
        t = CLE;
    } else if (str == "MIA") {
        t = MIA;
    }else if (str == "LA") {
        t = LA;
    } else if (str == "NYG") {
        t = NYG;
    } else if (str == "DAL") {
        t = DAL;
    } else if (str == "CAR") {
        t = CAR;
    } else if (str == "NO") {
        t = NO;
    } else if (str == "NE") {
        t = NE;
    }else if (str == "NYJ") {
        t = NYJ;
    } else if (str == "MIN") {
        t = MIN;
    } else if (str == "CHI") {
        t = CHI;
    } else if (str == "WAS") {
        t = WAS;
    } else if (str == "TEN") {
        t = TEN;
    } else if (str == "ATL") {
        t = ATL;
    }else if (str == "TB") {
        t = TB;
    } else if (str == "HOU") {
        t = HOU;
    } else if (str == "JAX") {
        t = JAX;
    } else if (str == "DET") {
        t = DET;
    } else if (str == "GB") {
        t = GB;
    } else if (str == "BUF") {
        t = BUF;
    }else if (str == "PHI") {
        t = PHI;
    }
    return t;
}

//loads a data set
void loadData(const string& str) {
    ifstream stream;
    stream.open(str);

    while (stream.good()) {
        string line;
        Play newPlay;

        getline(stream, line, ',');
        newPlay.gameID = stoi(line);

        getline(stream, line, ',');
        newPlay.date = line;

        getline(stream, line, ',');
        newPlay.quarter = stoi(line);

        getline(stream, line, ',');
        newPlay.minute = stoi(line);

        getline(stream, line, ',');
        newPlay.second = stoi(line);

        getline(stream, line, ',');
        newPlay.offenseTeam = stoTN(line);

        getline(stream, line, ',');
        newPlay.defenseTeam = stoTN(line);

        getline(stream, line, ',');
        newPlay.down = stoi(line);

        getline(stream, line, ',');
        newPlay.toGo = stoi(line);

        getline(stream, line, ',');
        newPlay.yardLine = stoi(line);

        getline(stream, line, ',');
        newPlay.seriesFirstDown = stoi(line);

        getline(stream, line, ',');
        newPlay.description = line;

        getline(stream, line, ',');
        newPlay.yards = stoi(line);

        getline(stream, line, ',');
        newPlay.formation = stoF(line);

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
        newPlay.isChallenge = stoi(line);

        getline(stream, line, ',');
        newPlay.isChallengeReversed = stoi(line);

        getline(stream, line, ',');
        newPlay.isMeasurement = stoi(line);

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
        newPlay.isPenaltyAccepted = stoi(line);

        getline(stream, line, ',');
        newPlay.penaltyTeam = stoTN(line);

        getline(stream, line, ',');
        newPlay.isNoPlay = stoi(line);

        getline(stream, line, ',');
        newPlay.penaltyYards = stoi(line);

        Game g;
        g.gameID = newPlay.gameID;
        g.offenseTeam = newPlay.offenseTeam;
        g.defenseTeam = newPlay.defenseTeam;
        g.gameDate = newPlay.date;
        g.plays.push_back(newPlay);


    }
    stream.close();
}

int main() {

    unordered_map<string, Team> teams;
    createTeams(teams);

    loadData("pbh-2018.csv");
}
