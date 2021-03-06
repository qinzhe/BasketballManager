#include "PositionPointGuard.h"

/** PositionCentre Constructor*/
PositionPointGuard::PositionPointGuard()
{
    int posMap[8][7] = {{2,5,5,5,5,5,5},
                     {2,5,5,3,3,3,3},
                     {2,5,5,3,2,2,2},
                     {2,5,4,3,2,1,1},
                     {2,5,4,3,2,1,1},
                     {2,5,5,3,2,2,2},
                     {2,5,5,3,3,3,3},
                     {2,5,5,5,5,5,5}};

    map.setMap(posMap);
}

/** Return the position Heatmap */
Heatmap PositionPointGuard::getMap()
{
    return map;
}

/** Return influence value of position x, y */
int PositionPointGuard::getValue(int x, int y)
{
    return map.getValue(x, y);
}

