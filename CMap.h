
#pragma once

#include <iostream>
#include <vector>
#include "CNest.h"
#include "CCoordinates.h"
#include "CTile.h"
#include "CAnt.h"

class CMap{
    public:
    int m_lenght = 70;
    int m_hight = 30;
    CTile map[70][30];
    vector<CNest> all_nests;
    vector<CAnt> all_ants;
    CNest * m_selected_nest = nullptr; 

    
    CMap();

    void add_nest(const CNest & src);

    void add_ant(const CAnt & src);

    void setfields_char(const CCoordinates & src, char c);

    void setfields_color(const CCoordinates & src, char c);

    void set_nest_selection(CNest * src);

    void clear_nest_selection(CNest * src);

    void setwall(const coords & first, const coords & second);

    void update_map(int tick);

    void update_nest(CNest * src,int tick);

    bool update_ant(CAnt * src, int tick);

    void attack(CNest * attacker, CNest * victim);

    void stop_attack(CNest * coward, CNest * chad);

    void clean_dead_bodies();

    void printmap();

    CTile & operator[](const coords & src);

    bool validate_path(CRoad & src);

    void select_next_nest();

    void reset_selection();
};   