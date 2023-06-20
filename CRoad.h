#pragma once

#include <iostream>
#include <vector>
#include "CCoordinates.h"

class CRoad{

    public:
        coords m_begin;
        coords m_end;

        vector<coords> road;

    CRoad(coords begin, coords end);

};
bool road_compare(CRoad & first, CRoad & second);