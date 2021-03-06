#ifndef POSITIONSHOOTINGGUARD_H
#define POSITIONSHOOTINGGUARD_H
#include "PlayerPosition.h"

/* Position Class for a Shooting Guard */
class PositionShootingGuard : public PlayerPosition
{
public:
    PositionShootingGuard();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;
};

#endif // POSITIONSHOOTINGGUARD_H
