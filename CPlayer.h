#pragma once

#include <iostream>
#include <vector>

#include "CNest.h"

class CPlayer{
    private:
    int dna_produc_speed;

    public:
    int dna_points;
    char m_color;
    vector<CNest*> players_nests;

    CPlayer(char color);

    void update_state(int tick);

    void add_nest(CNest * src);
};