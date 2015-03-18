#ifndef PLAYERSTRATEGYDYNAMIC_H
#define PLAYERSTRATEGYDYNAMIC_H
#include "PlayerStrategy.h"
class PlayerStrategyDynamic: public PlayerStrategy
{
public:
    PlayerStrategyDynamic();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYDYNAMIC_H
