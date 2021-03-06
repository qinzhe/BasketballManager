#include "PlayerStrategyDynamic.h"

/** PlayerStrategyDynamic Constructor */
PlayerStrategyDynamic::PlayerStrategyDynamic():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0}};

    map.setMap(strategyMap);
}

/** Return the heatmap */
Heatmap* PlayerStrategyDynamic::getMap()
{
    return &map;
}

/** Return the influence value at position x, y */
int PlayerStrategyDynamic::getValue(int x, int y)
{
    return map.getValue(x, y);
}

/** Return the probability vector of the strategy */
ProbabilityVector* PlayerStrategyDynamic::getWithBallVector()
{
    return &withBallVector;
}
