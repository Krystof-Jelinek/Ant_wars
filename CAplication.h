#pragma once

#include <iostream>
#include "CGame.h"

class CAplication{
    private:
    
    int state;
    
    public:
    void save_game();
    
    void load_game(){
        //configure game from files and set all values before starting the game
    }

    void start_game();
};