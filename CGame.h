#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "CPlayer.h"
#include "CMap.h"
#include "CInterface.h"


using namespace std;

class CGame{
    private:
    int state;
    int current_tick;
    vector<CPlayer> all_players;

    CMap map;
    public:

    CGame(){
        current_tick = 0;
    }

    void set_board();

    void set_skilltree_pointers();

    void add_player(CPlayer & src);

    void set_players_nests();

    void flush_players_nests();

    void start_game();

    void next_tick();

    void update_all_players();

    void show_options();
    
    void take_input();

    void take_upgrade_input();

    void show_upgrade_menu();

    CNest * select_nest();

    bool check_for_win();


    public:

};