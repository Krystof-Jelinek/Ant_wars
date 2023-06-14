#pragma once

#include <iostream>

#include "CAnt.h"

class CExplodingAnt: CAnt{

    CExplodingAnt(int health, int dmg, int speed,char color,coords position, coords destiny_position, shared_ptr<CRoad> road);


    bool move() override;
    void attack(CAnt * victim) override;
    void affect_nest() override;
};