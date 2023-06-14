#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include "CCoordinates.h"
#include "CAnt.h"
#include "CRoad.h"



using namespace std;

class CNest{
    private:
    
    //basic stats of the nest
    int m_health = 1500;
    int m_produc_speed = 5;
    
    //basic values for the produced ant, these will change with buffs
    int m_ant_health = 40;
    int m_ant_dmg = 40;
    int m_ant_speed = 2;

    public:

    //tmp v publicu

    char m_color = 'Y';
    int m_num_ants = 0;
    int m_currently_attacking = 0;
    int m_currently_attacking_num = 0;

    CCoordinates m_coordinates;
    vector<shared_ptr<CRoad>> m_connected_paths;
    vector<shared_ptr<CRoad>> m_attacking_paths;
    coords m_entrypoints[4];
    
    CNest();

    CNest(CCoordinates coordinates, char color);

    void setcoordinates(int x1, int x2, int y1, int y2);

    char first_ant_num() const ;

    char second_ant_num() const ;

    void show_upgrades(ostream & src);

    CRoad find_closest_path(CNest * attacker, CNest * victim);

    void state_update(int tick);

    bool create_ant_check(int tick);

    coords get_starting_coords();

    CAnt create_ant();

};

CRoad find_shortest_path(CNest * attacker, CNest * victim);