#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "ProbabilityVector.h"
#include "Heatmap.h"
#include "MatchScreen.h"
#include "MatchReceiver.h"
#include "Fouls.h"
#include "Analyser.h"
#include "MatchDefenceMan.h"
#include "MatchDefenceZone.h"

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <tuple>

#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>

/* Main class used for simulating matches. Holds
 * methods used for decision making and simulating
 * various aspects of a match.
 */
using namespace std;

class Match
{
public:
    Match(Team *teamOne, Team *teamTwo, MatchScreen *newScreen = NULL);

    ~Match();
    static void setSimSpeed(int speed);
    void sim();
    void writeMatchStats(string filename);

    static int simSpeed;

    int* getScore();
    Team *getTeamOne();
    Team *getTeamTwo();
private:
    Analyser analyser;
    MatchScreen *screen;
    Fouls fouls;
    MatchDefenceMan manDefence;
    MatchDefenceZone zoneDefence;
    int firstPossession;
    Heatmap shotMap;
    int gameState;
    const int INPLAY = 0, INBOUND = 1;
    Team * teamOne, *teamTwo;
    Team *teams[2];
    int shotClock, time, quarter;
    Ball ball;
    vector<Player*> orderOfPlay;
    tuple<Player *, int> assist;
    int score[2];
    const bool printing = false;
    bool endOfPossession;


    void guiUpdateCommentary(int type, Player *playerOne, Player *playerTwo = NULL);
    void guiUpdateStat();
    void guiUpdatePlayers();
    void guiInit();
    void guiUpdateCourt();

    void simPlayers();
    void move(Player* p);
    void withBall(Player* p, int shotClock);
    void driveBasket(Player *p);
    vector<int> getDefendersForPass(int team, int x1, int y1, int x2, int y2);
    int calculateStatModifier(Player *p);

    void shoot(Player* p, int pressure);
    void shootTwo(Player *p, int pressure, int shot, int shootRand, int foulRand, string type);
    //void shootUnderBasket(Player *p, int pressure);
    void shootThree(Player* p, int pressure);
    //void shootMedium(Player* p, int pressure);
    //void shootClose(Player* p, int pressure);
    void shootFreeThrow(Player* p, int numOfFreethrows);

    void pass(Player* p, Player* teamMate);
    void passInbound(Player* p);
    void rebound();
    void checkAssist();

    void moveDefence(Player* p);
    void moveDefenceLoose(Player *p, Player *opposition);
    void moveDefenceTight(Player* p, Player *opposition);
    void moveTowardBasket(Player* p);
    void moveDefender(Player *p, int destPosX, int destPosY);
    void moveZoneDefence(Player *p);
    void moveManDefence(Player *p);
    int flipY(int y);

    bool block(Player *p);
    void blockedShot(int posX, int posY);
    void steal(Player *p);

    void printCourt();
    void printValue(string valueName, int value);
    void printValue(string valueName, int value, int valueTwo);
    void printValue(string valueName);


    int getScoreDifference(int team);
    void jumpBall();
    void setOrderOfPlay();
    int getOtherTeam(int team);
    void swapSides(int playerNum);
    void setUpRestartInbound();
    void updateScore(int team, int points);

    void setUpOffensiveInbound();
    void setUpOwnSideInbound();

};

#endif // MATCH_H
