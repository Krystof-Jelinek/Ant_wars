#pragma once

#include <iostream>

#include "CAnt.h"

class CFlyingAnt:CAnt{

    CFlyingAnt(int health, int dmg, int speed,char color,bool sup,coords position, coords destiny_position, shared_ptr<CRoad> road);

    bool move() override;
    void attack(CAnt * victim);
    void affect_nest();

};