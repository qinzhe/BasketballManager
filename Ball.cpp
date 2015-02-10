#include "Ball.h"

Ball::Ball()
{
    team = 1;
    player = 5;
    posX = 0;
    posY = 4;
}

int Ball::getPlayerPosition()
{
    return player;
}
int Ball::getTeam()
{
    return team;
}

void Ball::setPlayerPosition(int num)
{
    player = num;
}

void Ball::setTeam(int team)
{
    if(team > 0 && team < 3)
    {
        this->team = team;
    }
}

void Ball::changeTeam()
{
    if(team == 1) team = 2;
    else if(team == 2) team = 1;
}

void Ball::changeTeam(int playerTeam)
{
    if(playerTeam == 1) team = 2;
    else if(playerTeam == 2) team = 1;
}

int Ball::getPosX()
{
    return posX;
}

int Ball::getPosY()
{
    return posY;
}

void Ball::setPos(int x, int y)
{
    posX = x;
    posY = y;
}

