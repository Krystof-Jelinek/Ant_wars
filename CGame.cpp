#include "CGame.h"

void CGame::set_board(){
    CNest green(CCoordinates(10,16,20,22),'G');
    CNest red(CCoordinates(20,26,6,8),'R');
    
    CNest gray(CCoordinates(40,46,3,5),'Y');
    CNest green2(CCoordinates(50,56,25,27),'G');

    string tmp = "jmeno";

    //green.m_tree.m_skills.push_back(make_shared<CFast_ant>(tmp,10));
    //green.m_tree.m_skills.push_back(make_shared<CStrong_ant>(tmp,10));
    //green.m_tree.m_skills.push_back(make_shared<CFast_rep>(tmp,10));
    //green.m_tree.m_skills.push_back(make_shared<CMore_sup>(tmp,10));




    map.add_nest(green);
    map.add_nest(red);
    //map.add_nest(gray);
    map.add_nest(green2);



    set_skilltree_pointers();
    set_players_nests();

    //map.setwall(coords(0,15),coords(20,15));

}

void CGame::set_skilltree_pointers(){
    for(auto itr = map.all_nests.begin(); itr != map.all_nests.end();itr++){
        (*itr).m_tree.set_ptr(&(*itr));
    }
}

void CGame::set_players_nests(){
    for(auto itr = map.all_nests.begin(); itr != map.all_nests.end();itr++){
        for(auto itr2 = all_players.begin(); itr2 != all_players.end();itr2++){
            if((*itr).m_color == (*itr2).m_color){
                (*itr2).add_nest(&(*itr));
            }
        }
    }
}

void CGame::flush_players_nests(){
    for(auto itr = all_players.begin(); itr != all_players.end();itr++){
        (*itr).players_nests.clear();
    }
}



CNest * CGame::select_nest(){
    while(true){
        map.printmap();
        cout << "Are you sure you want to select this nest ?" << endl;
        cout << "y - write \"y\" to confirm" << endl;
        cout << "n - write \"n\" to select next nest" << endl;
        cout << "c - write \"c\" to cancel" << endl;
        string input;
        getline(cin,input,'\n');
        if(input == "n"){
            map.select_next_nest();
        }
        if(input == "y"){
            map.clear_nest_selection(map.m_selected_nest);
            return map.m_selected_nest;
        }
        if(input == "c"){
            map.reset_selection();
            return map.m_selected_nest;
        }

    }
}

void CGame::next_tick(){
    current_tick++;
    update_all_players();
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

void CGame::take_input(){
    string input;
    getline(cin,input,'\n');

    if(map.m_selected_nest == nullptr){
        if(input == ""){
            next_tick();
            return;
        }

        if(input == "n"){
            map.select_next_nest();
            map.printmap();
            return;
        }

        else{
            map.printmap();
            cout << "Invalid input" << endl;
            return;
        }
    }

    if(input == ""){
        next_tick();
        return;
    }

    if(input == "c"){
        map.reset_selection();
        map.printmap();
        return;
    }

    if(input == "n"){
        map.select_next_nest();
        map.printmap();
        return;
    }

    if(input == "a"){
        cout << "Where you wanna sent ants ?" << endl;
        CNest * attacker = map.m_selected_nest;
        CNest * victim = select_nest();
        
        // the selection was canceled by user 
        if(victim == nullptr){
            map.printmap();
            return;
        }

        if(attacker == victim){
            map.reset_selection();
            map.printmap();
            cout << "You cant send ants to yourself!" << endl;
            return; 
        }
        map.attack(attacker,victim);
        map.reset_selection();
        map.printmap();
        return;
    }

    //for stopping an attack on nest
    if(input == "j"){
        if(map.m_selected_nest->m_attacking_paths.empty()){
            map.printmap();
            cout << "You cant stop sending ants when there is no sending happening" << endl;
            return;
        }

        CNest * coward = map.m_selected_nest;
        CNest * chad = select_nest();
        
        // the selection was canceled by user
        if(chad == nullptr){
            map.printmap();
            return;
        }

        if(coward == chad){
            map.reset_selection();
            map.printmap();
            cout << "You cant do this!" << endl;
            return; 
        }

        map.stop_attack(coward,chad);
        map.reset_selection();
        map.printmap();
        return;
    
    }

    //for opening the upgrade menu
    if(input == "u"){
        
    }

    else{
        cout << "Invalid Input!" << endl;
    }
}

void CGame::show_options(){
    if(map.m_selected_nest == nullptr){
        cout << "\\n - press enter for playing next turn" << endl;
        cout << "n - write \"n\" to start selecting nests" << endl;
    }

    else{
        cout << "a - write \"a\" to send ants from this nest" << endl;
        cout << "j - write \"j\" to stop sending ants from this nest" << endl;
        cout << "u - write \"u\" to open upgrade menu for this nest" << endl;
        cout << "c - write \"c\" to stop nest selection mode" << endl;
        cout << "n - write \"n\" to select next nest" << endl;
        cout << "\\n - press enter for playing next turn" << endl;

    }

}

void CGame::update_all_players(){
    flush_players_nests();
    set_players_nests();
    for(auto itr = all_players.begin(); itr != all_players.end();itr++){
        (*itr).update_state(current_tick);
    }
}





void CGame::start_game(){
    map.printmap();
    while(true){
 
        show_options();
        take_input();

        if(check_for_win()){
            next_tick();
            map.printmap();
            cout << map.all_nests[0].m_color << " HAS WON THE GAME" << endl;
            break;
        }
    }
}