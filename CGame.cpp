#include "CGame.h"

void CGame::set_board(){
    CNest green(CCoordinates(10,16,20,22),'G');
    CNest red(CCoordinates(20,26,6,8),'R');
    
    CNest gray(CCoordinates(40,46,3,5),'Y');
    CNest green2(CCoordinates(50,56,25,27),'G');

    map.add_nest(green);
    map.add_nest(red);
    //map.add_nest(gray);
    map.add_nest(green2);

    //map.setwall(coords(0,15),coords(20,15));

}

CNest * CGame::select_nest(){
    while(true){
        map.printmap();
        cout << "Are you sure you want to select this nest ?" << endl;
        char c = getchar();
        if(c == 'n'){
            map.select_next_nest();
        }
        if(c == 'y'){
            return map.m_selected_nest;
        }
    }
}

void CGame::next_tick(){
    current_tick++;
    map.update_map(current_tick);
    map.printmap();
}

bool CGame::check_for_win(){
    char color = map.all_nests[0].m_color;
    for(auto itr = map.all_nests.begin();itr != map.all_nests.end();itr++){
        if((*itr).m_color != color){
            return false;
        }
    }
    return true;
}



void CGame::start_game(){
    while(1){

 
        char c = getchar();
        if(c == 'q'){
            break;
        }
        if(c == 'n'){
            map.select_next_nest();
            map.printmap();
            continue;
        }

        if(c == 'u'){
            cout << "Where you wanna sent ants ?" << endl;

            CNest * attacker = map.m_selected_nest;
            CNest * victim = select_nest();

            if(attacker == victim){
                cout << "You cant send ants to yourself!" << endl;
                return; 
            }

            map.attack(attacker,victim);

        }

        next_tick();
        if(check_for_win()){
            next_tick();
            map.printmap();
            cout << map.all_nests[0].m_color << " HAS WON THE GAME" << endl;
            break;
        }
    }
}