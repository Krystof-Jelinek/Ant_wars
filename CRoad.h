#pragma once

#include <iostream>
#include <vector>
#include "CCoordinates.h"

class CRoad{

    public:
        coords m_begin;
        coords m_end;

        //CNest * m_nest_begin;
        //CNest * m_nest_end;


        vector<coords> road;


    CRoad(coords begin, coords end);

};

bool road_compare(CRoad & first, CRoad & second);