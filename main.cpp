#include <iostream>
#include <cassert>
#include "CNest.h"
#include "CAnt.h"
#include "CMap.h"
#include "CRoad.h"
#include "CGame.h"




int main(void){

    CGame game;

    game.set_board();
    game.start_game();
    
    return 0;
}