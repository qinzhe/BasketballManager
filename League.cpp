#include "League.h"

#include <sstream>
League::League()
{
    createSchedule("../schedule.xml");
    teams[1] = new LeagueTeam("Spurs", true);
    teams[2] = new LeagueTeam("Pacers");
    teams[3] = new LeagueTeam("Heat");
    teams[4] = new LeagueTeam("Bobcats");
    currentRound = 1;
    teamCount = teams.size();
}

void League::simRound()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(auto &match: matches)
    {

        LeagueTeam *homeTeam = teams[get<0>(match)];
        LeagueTeam *awayTeam = teams[get<1>(match)];
        Match m(homeTeam->getTeam(), awayTeam->getTeam());
        m.setSimSpeed(0);
        m.sim();
        int scoreHome = m.getScore()[0], scoreAway = m.getScore()[1];
        if(scoreHome > scoreAway)
        {
            homeTeam->addWin();
            awayTeam->addGame();
        }
        else
        {
            awayTeam->addWin();
            homeTeam->addGame();
        }
        results.push_back(homeTeam->getTeam()->getName() + " " + to_string(scoreHome) + "-" +
                                    to_string(scoreAway) +" "+awayTeam->getTeam()->getName());
    }

    currentRound++;
}

void League::createSchedule(const char* file)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file);

    //loop through the tree structure created of the xml
    for (pugi::xml_node game: doc.child("schedule"))
    {
        map<string, int> gameMap;
        roundCount = stoi(game.first_attribute().value());
        teamCount = stoi(game.last_attribute().value());

        for (pugi::xml_attribute attr: game.attributes())
        {
            gameMap[attr.name()] = stoi(attr.value());
        }
        tuple <int, int> matchup = make_tuple(gameMap["home"], gameMap["away"]);
        int round = gameMap["round"];
        if(schedule.find(round) == schedule.end())
        {
            vector<tuple<int, int>> newRound;
            newRound.push_back(matchup);
            schedule[round] = newRound;
        }
        else
        {
            schedule[round].push_back(matchup);
        }
    }
}

int League::findWinner()
{
    int winner = 0;
    int wins = 0;
    for(auto &team: teams)
    {
        if(team.second->getWins() > wins)
        {
            winner = team.first;
            wins = team.second->getWins();
        }
    }
    return winner;
}

//=================================
// GUI
//=================================

vector<tuple<int, int>> League::getNextRound()
{
    return schedule[currentRound];
}

vector<string> League::getResults()
{
     return results;
}

LeagueTeam* League::getTeam(int index)
{
    return teams[index];
}

tuple<int, int> League::getUserMatch()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(auto &match: matches)
    {
        if(teams[get<0>(match)]->isUserControlled() || teams[get<1>(match)]->isUserControlled())
        {
            return match;
        }
    }
}

void League::removeUserMatch()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(int i = 0; i < matches.size(); i++)
    {
        tuple<int, int> match = matches[i];
        if(teams[get<0>(match)]->isUserControlled() || teams[get<1>(match)]->isUserControlled())
        {
            matches.erase(matches.begin() + i);
            break;
        }
    }
}

vector<LeagueTeam *> League::getAllTeams()
{
    vector<LeagueTeam *> allTeams;

    for(auto &team: teams)
    {
        allTeams.push_back(team.second);
    }

    return allTeams;
}

vector<LeagueTeam *> League::getStandings()
{
    vector<LeagueTeam *> allTeams = getAllTeams();
    vector<LeagueTeam *> standings;

    while(allTeams.size() > 0)
    {

        LeagueTeam *nextTeam = allTeams[allTeams.size() - 1];
        allTeams.pop_back();
        int i;
        for(i = standings.size(); i > 0; i--)
        {
            if(*standings[i - 1] > *nextTeam)
            {
                break;
            }
        }
        standings.insert(standings.begin() + i, nextTeam);
    }
    return standings;
}

int League::getTeamCount()
{
    return teamCount;
}

//==================================
// Stats
//==================================

string League::getPointsLeader()
{
    string teamName, playerName;
    float points = -1;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i < 11; i++)
        {
            float currentPoints = currentTeam->getPlayer(i)->getOverAllStatList()->getPointsPerGame();
            if(currentPoints > points)
            {
                points = currentPoints;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(points);
    return resultString;
}

string League::getFieldGoalLeader()
{
    string teamName, playerName;
    float fgpc = -1;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i < 11; i++)
        {
            float currentFGPC = currentTeam->getPlayer(i)->getOverAllStatList()->getShootingPercentage();
            if(currentFGPC > fgpc)
            {
                fgpc = currentFGPC;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(fgpc);
    return resultString;
}

string League::getThreePointLeader()
{
    string teamName, playerName;
    float tppc = -1;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i < 11; i++)
        {
            float currentTPPC = currentTeam->getPlayer(i)->getOverAllStatList()->getThreeShootingPercentage();
            if(currentTPPC > tppc)
            {
                tppc = currentTPPC;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(tppc);
    return resultString;
}

//==================================
// Printing
//==================================

void League::printResults()
{
    for(auto &result: results)
    {
        cout << result << endl;
    }
}

void League::printTable()
{
    cout << "T|G|W|L" << endl;
    for(auto &team: teams)
    {
        cout << team.first << " " << team.second->getGames() << " " << team.second->getWins() << " " << team.second->getLosses() << endl;
    }
}

void League::printSchedule()
{
    for(int i = 1; i <= roundCount; i++)
    {
        vector<tuple<int, int>> round = schedule[i];
        cout << "ROUND: " << i << endl;
        for(int j = 0; j < round.size(); j++)
        {
            cout << "HOME: " << get<0>(round[j]) << " AWAY: " << get<1>(round[j]) << endl;
        }
    }
}

void League::printSchedule(int team)
{
    for(int i = 1; i <= roundCount; i++)
    {
        vector<tuple<int, int>> round = schedule[i];
        cout << "ROUND: " << i << endl;
        for(int j = 0; j < round.size(); j++)
        {
            if(get<0>(round[j]) == team || get<1>(round[j]) == team)
            {
                cout << "HOME: " << get<0>(round[j]) << " AWAY: " << get<1>(round[j]) << endl;
            }
        }
    }
}

