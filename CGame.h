#pragma once

#include <iostream>
#include <vector>
#include "CPlayer.h"
#include "CMap.h"

using namespace std;

class CGame{
    private:
    int state;
    int current_tick;
    vector<CPlayer*> all_players;

    CMap map;
    public:

    CGame(){
        current_tick = 0;
    }

    void set_board();

    void start_game();

    void next_tick();

    CNest * select_nest();

    bool check_for_win();

    public:

};