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

    CGame(){
        current_tick = 0;
    }

    void set_board();

    void start_game();

    void next_tick();

    bool check_for_win();

    public:

};