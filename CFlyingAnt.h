#pragma once

#include <iostream>

#include "CAnt.h"

class CFlyingAnt : public CAnt{
    public:
    CFlyingAnt(int health, int dmg, int speed,char color,bool sup,coords position, coords destiny_position, shared_ptr<CRoad> road);

    bool move() override;
    void affect_nest();

};