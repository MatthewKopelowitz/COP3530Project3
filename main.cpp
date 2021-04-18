#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "Team.h"
//#include "../../Downloads/COP3530Project3-main 3/Team.h"
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
    bool isSingleTeam = false; //user selection variable
    cout << "MENU OPTIONS" << endl;
    cout << "1. Single Team" << endl;
    cout << "2. Top X" << endl;
    cout << "Please input a number" << endl;

    cin >> menuChoice;
    int_MC = stoi(menuChoice);

    //asks the user if they want to see stats for a single team or for top ten teams and records input in isSingleTeam boolean
    switch (int_MC) {
        case 1:
            isSingleTeam = true;
            break;
        case 2:
            isSingleTeam = false;
            break;
    }

    //asks user which team they would like to see stats for
    if (isSingleTeam) {
        string selectedTeam = ""; //user selection variable
        cout << "MENU OPTIONS" << endl;
        cout << "Which Team Would You Like to See Stats For?" << endl;
        cout << "1. PIT" << endl;
        cout << "2. LV" << endl;
        cout << "3. KC" << endl;
        cout << "4. BAL" << endl;
        cout << "5. ARI" << endl;
        cout << "6. LAC" << endl;
        cout << "7. SF" << endl;
        cout << "8. IND" << endl;
        cout << "9. SEA" << endl;
        cout << "10. DEN" << endl;
        cout << "11. CIN" << endl;
        cout << "12. CLE" << endl;
        cout << "13. MIA" << endl;
        cout << "14. LA" << endl;
        cout << "15. NYG" << endl;
        cout << "16. DAL" << endl;
        cout << "17. CAR" << endl;
        cout << "18. NO" << endl;
        cout << "19. NE" << endl;
        cout << "20. NYJ" << endl;
        cout << "21. MIN" << endl;
        cout << "22. CHI" << endl;
        cout << "23. WAS" << endl;
        cout << "24. TEN" << endl;
        cout << "25. ATL" << endl;
        cout << "26. TB" << endl;
        cout << "27. HOU" << endl;
        cout << "28. JAX" << endl;
        cout << "29. DET" << endl;
        cout << "30. GB" << endl;
        cout << "31. BUF" << endl;
        cout << "32. PHI" << endl;
        cout << "Please input a number" << endl;

        cin >> menuChoice;
        int_MC = stoi(menuChoice);

        switch(int_MC) {
            case 1:
                selectedTeam = "PIT";
                break;
            case 2:
                selectedTeam = "LV";
                break;
            case 3:
                selectedTeam = "KC";
                break;
            case 4:
                selectedTeam = "BAL";
                break;
            case 5:
                selectedTeam = "ARI";
                break;
            case 6:
                selectedTeam = "LAC";
                break;
            case 7:
                selectedTeam = "SF";
                break;
            case 8:
                selectedTeam = "IND";
                break;
            case 9:
                selectedTeam = "SEA";
                break;
            case 10:
                selectedTeam = "DEN";
                break;
            case 11:
                selectedTeam = "CIN";
                break;
            case 12:
                selectedTeam = "CLE";
                break;
            case 13:
                selectedTeam = "MIA";
                break;
            case 14:
                selectedTeam = "LA";
                break;
            case 15:
                selectedTeam = "NYG";
                break;
            case 16:
                selectedTeam = "DAL";
                break;
            case 17:
                selectedTeam = "CAR";
                break;
            case 18:
                selectedTeam = "NO";
                break;
            case 19:
                selectedTeam = "NE";
                break;
            case 20:
                selectedTeam = "NYJ";
                break;
            case 21:
                selectedTeam = "MIN";
                break;
            case 22:
                selectedTeam = "CHI";
                break;
            case 23:
                selectedTeam = "WAS";
                break;
            case 24:
                selectedTeam = "TEN";
                break;
            case 25:
                selectedTeam = "ATL";
                break;
            case 26:
                selectedTeam = "TB";
                break;
            case 27:
                selectedTeam = "HOU";
                break;
            case 28:
                selectedTeam = "JAX";
                break;
            case 29:
                selectedTeam = "DET";
                break;
            case 30:
                selectedTeam = "GB";
                break;
            case 31:
                selectedTeam = "BUF";
                break;
            case 32:
                selectedTeam = "PHI";
                break;
        }
    }

    //simple unordered map just to keep track of which seasons the user selects to show stats for
    unordered_map<string, bool> sznSelect; //user selection variable
    sznSelect["2018"] = false;
    sznSelect["2019"] = false;
    sznSelect["2020"] = false;

    cout << "MENU OPTIONS" << endl;
    cout << "1. 2018 Season" << endl;
    cout << "2. 2019 Season" << endl;
    cout << "3. 2020 Season" << endl;
    cout << "4. All 3 Seasons" << endl;
    cout << "Please input a number" << endl;

    cin >> menuChoice;
    int_MC = stoi(menuChoice);

    //asks the user which season(s) they want to see stats for and stores their input as booleans in the unordered_map sznSelect
    switch (int_MC) {
        case 1:
            sznSelect["2018"] = true;
            break;
        case 2:
            sznSelect["2019"] = true;
            break;
        case 3:
            sznSelect["2020"] = true;
            break;
        case 4:
            sznSelect["2018"] = true;
            sznSelect["2019"] = true;
            sznSelect["2020"] = true;
            break;
    }

    cout << "MENU OPTIONS" << endl;
    cout << "Select Which Stat You Would Like to See" << endl;
    cout << "1. Number of games won by majority plays being running vs passing" << endl;
    cout << "2. First down completion success rate on running vs passing plays" << endl;
    cout << "3. Average yards gained on running vs passing plays" << endl;
    cout << "4. Chance of any play gaining 30+ yards for running vs passing" << endl;
    cout << "5. Chance of any play being a turnover for running vs passing" << endl;
    cout << "6. Average yards gained in shotgun formation vs other formations" << endl;
    cout << "7. Chance of penalty on offense vs defense on running vs passing play" << endl;
    cout << "Please input a number" << endl;

    cin >> menuChoice;
    int_MC = stoi(menuChoice);

    //switch between sorting according to which stat the user selected
    vector<Team> sortedTeams;
    switch (int_MC) {
    /*case 1:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 2:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 3:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 4:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 5:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 6:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
    case 7:
        sortedTeams = bubbleSort();
        sortedTeams = heapSort();
        break;
        */
    }
    
    return 0;
}