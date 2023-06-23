#pragma once

#include <iostream>

#include "CAnt.h"

class CExplodingAnt: public CAnt{
    public:
    CExplodingAnt(int health, int dmg, int speed,char color,bool sup,coords position, coords destiny_position, shared_ptr<CRoad> road);


    void attack(shared_ptr<CAnt> victim) override;
    void affect_nest() override;
};