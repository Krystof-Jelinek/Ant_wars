#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "CRoad.h"
#include "CCoordinates.h"



class CAnt{
    public:

    int m_health;
    int m_speed;
    int m_dmg;
    char m_color;

    bool m_support_boost;

    shared_ptr<CRoad> m_road;
    coords m_position;
    coords m_destiny_coords;



    CAnt();

    CAnt(int health, int dmg, int speed,char color, bool sup_boost,coords position, coords destiny_position, shared_ptr<CRoad> road);

    bool update_map_state(int tick);

    void set_destiny_coords(const coords & src );

    virtual bool move();

    virtual void attack(CAnt * victim);

    virtual void affect_nest();
};