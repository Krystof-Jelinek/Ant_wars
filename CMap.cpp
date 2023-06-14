#include "CMap.h"

CMap::CMap(){
    for(int j = 0; j < m_hight; j++){
        for(int i = 0; i< m_lenght; i++){
            if((i == 0)||(i == m_lenght -1)){
                map[i][j].set_char('#');
            }
            else if((j == 0)||(j == m_hight -1)){
                map[i][j].set_char('#');
            }
        }
    }
}

void CMap::add_nest(const CNest & src){
    all_nests.push_back(src);
}

void CMap::add_ant(const CAnt & src){
    all_ants.push_back(src);
}

void CMap::setfields_char(const CCoordinates & src, char c){
     for(int j = 0; j < m_hight;j++){
        for(int i = 0; i< m_lenght;i++){ 
            if(((i >= src.m_x1) && (i <= src.m_x2))&&((j >= src.m_y1) &&( j <= src.m_y2))){
                map[i][j].set_char(c);
            }
        }
    }
} 

void CMap::setfields_color(const CCoordinates & src, char c){
    for(int j = 0; j < m_hight;j++){
        for(int i = 0; i< m_lenght;i++){ 
            if(((i >= src.m_x1) && (i <= src.m_x2))&&((j >= src.m_y1) &&( j <= src.m_y2))){
                map[i][j].set_color(c);
            }
        }
    }
}

void CMap::set_nest_selection(CNest * src){
    
    for(int i = src->m_coordinates.m_x1; i <= src->m_coordinates.m_x2;i++){
        map[i][src->m_coordinates.m_y1 -1].set_selection_char('-');
        map[i][src->m_coordinates.m_y2 +1].set_selection_char('-');
    }

    for(int i = src->m_coordinates.m_y1; i <= src->m_coordinates.m_y2;i++){
        map[src->m_coordinates.m_x1 -1][i].set_selection_char('|');
        map[src->m_coordinates.m_x2 +1][i].set_selection_char('|');
    }
    map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y1 -1].set_selection_char('+');
    map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y1 -1].set_selection_char('+');
    map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y2 +1].set_selection_char('+');
    map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y2 +1].set_selection_char('+');


}

void CMap::clear_nest_selection(CNest * src){
    for(int i = src->m_coordinates.m_x1; i <= src->m_coordinates.m_x2;i++){
        if(map[i][src->m_coordinates.m_y1 -1].m_ant_ocup == nullptr){
            map[i][src->m_coordinates.m_y1 -1].reset_tile();
        }
        if(map[i][src->m_coordinates.m_y2 +1].m_ant_ocup == nullptr){
            map[i][src->m_coordinates.m_y2 +1].reset_tile();       
        }
    }

    for(int i = src->m_coordinates.m_y1; i <= src->m_coordinates.m_y2;i++){
        if(map[src->m_coordinates.m_x1 -1][i].m_ant_ocup == nullptr){
            map[src->m_coordinates.m_x1 -1][i].reset_tile();       
        }
        if(map[src->m_coordinates.m_x2 +1][i].m_ant_ocup == nullptr){
            map[src->m_coordinates.m_x2 +1][i].reset_tile();       
        }
    }
    if(map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y1 -1].m_ant_ocup == nullptr){
        map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y1 -1].reset_tile();
    }
    if(map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y1 -1].m_ant_ocup == nullptr){
        map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y1 -1].reset_tile();
    }
    if(map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y2 +1].m_ant_ocup == nullptr){
        map[src->m_coordinates.m_x1 -1][src->m_coordinates.m_y2 +1].reset_tile();
    }
    if(map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y2 +1].m_ant_ocup == nullptr){
        map[src->m_coordinates.m_x2 +1][src->m_coordinates.m_y2 +1].reset_tile();
    }
}

void CMap::setwall(const coords & first, const coords & second){
    
    int x1 = min(first.m_x,second.m_x);
    int x2 = max(first.m_x,second.m_x);
    int y1 = min(first.m_y,second.m_y);
    int y2 = max(first.m_y,second.m_y);
    
    //check if wall is in boundaries
    if((x1 < 0)||(x2 > m_lenght)){
        throw std::logic_error("Walls cant be outside of the map");
    }
    if((y1 < 0)||(y2 > m_hight)){
        throw std::logic_error("Walls cant be outside of the map");
    }
    
    //wall can only be straight
    if((x1 != x2)&&(y1 != y2)){
        throw std::logic_error("Wall can only be straight!");
    }

    if(x1 == x2){
        while(y1 <= y2){
            this->map[x1][y1].set_char('#');
            y1++;
        }
        return;
    }

    if(y1 == y2){
        while(x1 <= x2){
            this->map[x1][y1].set_char('#');
            x1++;
        }
        return;
    }
}

CTile & CMap::operator[](const coords & src){
    return map[src.m_x][src.m_y];
}

void CMap::update_nest(CNest * src,int tick){
    src->state_update(tick);
    this->setfields_color(src->m_coordinates,src->m_color);
    this->map[src->m_coordinates.m_x1 + 4][src->m_coordinates.m_y1 + 1].set_char(src->first_ant_num());
    this->map[src->m_coordinates.m_x1 + 3][src->m_coordinates.m_y1 + 1].set_char(src->second_ant_num());
    this->map[src->m_coordinates.m_x1 + 2][src->m_coordinates.m_y1 + 1].set_char('X');

    if(src == m_selected_nest){
        this->set_nest_selection(src);
    }


    //nastavime pointery na polickach na mraveniste co tam je
    this->map[src->m_coordinates.m_x1][src->m_coordinates.m_y1 +1].m_nest_ocup = src;
    this->map[src->m_coordinates.m_x1 + 3][src->m_coordinates.m_y1].m_nest_ocup = src;
    this->map[src->m_coordinates.m_x1 + 3][src->m_coordinates.m_y2].m_nest_ocup = src;
    this->map[src->m_coordinates.m_x2][src->m_coordinates.m_y1 +1].m_nest_ocup = src;

    if(src->create_ant_check(tick) == true){
        all_ants.push_back(src->create_ant());
    }

}

bool CMap::update_ant(CAnt * src, int tick){

    if(src->m_health <= 0){
        return true;
    }

    //smaze nejdrive svuj pointer z mista ze ktereho odchazi
    (*this)[src->m_position].reset_tile();

    //aktualizuje svoji pozici
    src->update_map_state(tick);
    
    if((*this)[src->m_position].m_ant_ocup != nullptr){
        
        if((*this)[src->m_position].m_ant_ocup->m_color != src->m_color){
        //musi dojit k fightu
            
            
            CAnt * enemy = (*this)[src->m_position].m_ant_ocup;
            while((src->m_health > 0)&&(enemy->m_health > 0)){
                src->m_health = src->m_health - enemy->m_dmg;
                enemy->m_health = enemy->m_health - src->m_dmg;
            }

            if((src->m_health <= 0)&&(enemy->m_health <= 0)){
                (*this)[src->m_position].reset_tile();
                return false;
            }
            
            if(src->m_health <= 0){
                return false;
            }

        }

    }

    //pokud dorazil do hnizda

    if(((*this)[src->m_position].m_nest_ocup != nullptr)&&(src->m_position == src->m_destiny_coords)){
        CNest * nest_ptr = (*this)[src->m_position].m_nest_ocup;

        if(nest_ptr->m_color != src->m_color){
            nest_ptr->m_num_ants = nest_ptr->m_num_ants -1;
            if(nest_ptr->m_num_ants == -1){
                nest_ptr->m_color = src->m_color;
                nest_ptr->m_num_ants = 1;
            }
            return true;
        }

        if(nest_ptr->m_color == src->m_color){
            nest_ptr->m_num_ants = nest_ptr->m_num_ants +1;
            return true;
        }

    }

    if(src->m_health > 0){
        (*this)[src->m_position].set_char(src->m_color);
        (*this)[src->m_position].set_color(src->m_color);
        (*this)[src->m_position].m_ant_ocup = src;
    }
    return false;

}

void CMap::attack(CNest * attacker, CNest * victim){
    
    CRoad tmp_path = find_shortest_path(attacker,victim);

    if (validate_path(tmp_path) == false){
        cout << "Na toto mraveniste nelze zautocit" << endl;
        return;
    }

    //checking wheter the attacker isnt already attacking this nest
    for(auto itr = attacker->m_attacking_paths.begin();itr != attacker->m_attacking_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            cout << "You already attack there!" << endl;
            return;
        }
    }

    //checking wheter the victim isnt allay and isnt already sending his units to the "attacker"
    if(attacker->m_color == victim->m_color){
        for(auto itr = victim->m_attacking_paths.begin();itr != victim->m_attacking_paths.end();itr++){
            if(road_compare((*(*itr).get()),tmp_path)){
                cout << "You cant send ants in between two nests" << endl;
                return;
            }
        }
    }

    //if such path already exists i only use it as attacking path
    for(auto itr = attacker->m_connected_paths.begin();itr != attacker->m_connected_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            attacker->m_attacking_paths.push_back((*itr));
            attacker->m_currently_attacking_num = attacker->m_currently_attacking_num + 1;
            return;
            return;
        }
    }

    //if such path doesnt exist and its given to the attacker and also the defender but only the attacking one will be sending ants there
    shared_ptr<CRoad> pointer = make_shared<CRoad>(tmp_path);


    attacker->m_connected_paths.push_back(pointer);
    attacker->m_attacking_paths.push_back(pointer);
    
    victim->m_connected_paths.push_back(pointer);

    attacker->m_currently_attacking_num = attacker->m_currently_attacking_num + 1;



}

void CMap::stop_attack(CNest * coward, CNest * chad){
    bool flag = false;
    CRoad tmp_path = find_shortest_path(coward,chad);

    //find and delete the road from attacking
    for(auto itr = coward->m_attacking_paths.begin();itr != coward->m_attacking_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            coward->m_attacking_paths.erase(itr);
            coward->m_currently_attacking_num--;
            flag = true;
            break;
        }
    }
    if(flag == false){
        cout << "You dont even attack here!" << endl;
        return;
    }

    //check if the second guy is still attacking if hes not both roads should be deleted
    for(auto itr = chad->m_attacking_paths.begin();itr != chad->m_attacking_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            return;
        }
    }

    //deleting the roads that are not used
    for(auto itr = coward->m_connected_paths.begin();itr != coward->m_connected_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            coward->m_connected_paths.erase(itr);
            break;
        }
    }

    for(auto itr = chad->m_connected_paths.begin();itr != chad->m_connected_paths.end();itr++){
        if(road_compare((*(*itr).get()),tmp_path)){
            chad->m_connected_paths.erase(itr);
            break;
        }
    }

}

void CMap::select_next_nest(){
    this->clear_nest_selection(m_selected_nest);
    for(auto itr = all_nests.begin(); itr != all_nests.end();itr++){
        if((&(*itr)) == m_selected_nest){
            itr++;
            if(itr == all_nests.end()){
                m_selected_nest = &(*all_nests.begin());
                set_nest_selection(m_selected_nest);
                return;
            }
            else{
                m_selected_nest = &(*(itr));
                set_nest_selection(m_selected_nest);
                return;
            }
        }
    }
}

bool CMap::validate_path(CRoad & src){
    for(auto itr = src.road.begin();itr != src.road.end();itr++){
        if((*this)[(*itr)].is_wall()){
            return false;
        }
    }
    return true;
}

void CMap::clean_dead_bodies(){

    for(auto itr = all_ants.begin();itr != all_ants.end();){
        if((*itr).m_health <= 0){
            itr = all_ants.erase(itr);
            continue;
        }
        itr++;
    }

}

void CMap::update_map(int tick){

    for(auto itr = all_nests.begin();itr != all_nests.end();itr++){
        this->update_nest(&(*itr),tick);
    }

    for(auto itr = all_ants.begin();itr != all_ants.end();){
        
        if(this->update_ant(&(*itr),tick) == true){
            itr = all_ants.erase(itr);
            continue;
        }
        itr++;
    }

    this->clean_dead_bodies();
}   

void CMap::printmap(){
    for(int j = 0; j < m_hight;j++){
        for(int i = 0; i< m_lenght;i++){ 
            map[i][j].print_tile();
        }
        std::cout << std::endl;
    }
}