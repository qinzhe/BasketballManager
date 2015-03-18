#include "PlayerStrategyBalancedPlaymaker.h"

PlayerStrategyBalancedPlaymaker::PlayerStrategyBalancedPlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,0,8,8,8,8,0})
{
    int strategyMap[8][7] = {{1,6,6,6,6,6,6},
                             {1,6,6,6,6,6,6},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,6,6,6,6},
                             {1,6,6,6,6,6,6}};

    map.setMap(strategyMap);
}

Heatmap* PlayerStrategyBalancedPlaymaker::getMap()
{
    return &map;
}

int PlayerStrategyBalancedPlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector* PlayerStrategyBalancedPlaymaker::getWithBallVector()
{
    return &withBallVector;
}
