#include "CNest.h"

CNest::CNest(){
        m_health = 1000;
        m_produc_speed = 5;
        m_ant_dmg = 20;
        m_ant_health = 60;
        m_ant_speed = 3;
        m_color = 'Y';
    }

CNest::CNest(CCoordinates coordinates, char color){
    m_coordinates = coordinates;
    m_color = color;
    m_entrypoints[0] = coords(m_coordinates.m_x1,m_coordinates.m_y1 +1);
    m_entrypoints[1] = coords(m_coordinates.m_x2,m_coordinates.m_y1 +1);
    m_entrypoints[2] = coords(m_coordinates.m_x1 + 3,m_coordinates.m_y1);
    m_entrypoints[3] = coords(m_coordinates.m_x1 + 3,m_coordinates.m_y2);
}

void CNest::setcoordinates(int x1, int x2, int y1, int y2){
    m_coordinates = CCoordinates(x1,x2,y1,y2);
}

char CNest::first_ant_num() const {
    return char(m_num_ants%10 + '0');
}

char CNest::second_ant_num() const {
    return char((floor(m_num_ants /10.0)) + '0');
}

void CNest::state_update(int tick){
    if(tick%m_produc_speed == 0){
        if(m_color == 'Y'){
            return;
        }
        m_num_ants++;
    }
}

bool CNest::create_ant_check(int tick){
    if(m_attacking_paths.empty()){
        return false;
    }

    if(m_currently_attacking_num == 0){
        return false;
    }
    
    if(tick % m_produc_speed == 0){
        return true;
    }
    return false;
}

coords CNest::get_starting_coords(){
    switch(m_currently_attacking){
        case 0:
            if(this->m_coordinates.includes(m_attacking_paths[0].get()->m_begin)){
                return m_attacking_paths[0].get()->m_begin;
            }
            else{
                return m_attacking_paths[0].get()->m_end;
            }
            break;
        case 1:
            if(this->m_coordinates.includes(m_attacking_paths[1].get()->m_begin)){
                return m_attacking_paths[1].get()->m_begin;
            }
            else{
                return m_attacking_paths[1].get()->m_end;
            }
            break;
        case 2:
            if(this->m_coordinates.includes(m_attacking_paths[2].get()->m_begin)){
                return m_attacking_paths[2].get()->m_begin;
            }
            else{
                return m_attacking_paths[2].get()->m_end;
            }
            break;
        case 3:
            if(this->m_coordinates.includes(m_attacking_paths[3].get()->m_begin)){
                return m_attacking_paths[3].get()->m_begin;
            }
            else{
                return m_attacking_paths[3].get()->m_end;
            }
            break;            
    }

    throw invalid_argument("Mistake in getting starting coordinates for ant!");
}

CAnt CNest::create_ant(){

    if(m_currently_attacking == m_currently_attacking_num){
        m_currently_attacking = 0;
    }

    coords starting = get_starting_coords();

    coords ending;
    if(starting.distance(m_attacking_paths[m_currently_attacking].get()->m_end) < starting.distance(m_attacking_paths[m_currently_attacking].get()->m_begin)){
        ending = m_attacking_paths[m_currently_attacking].get()->m_begin;
    }
    else{
        ending = m_attacking_paths[m_currently_attacking].get()->m_end;
    }


    CAnt tmp(m_ant_health, m_ant_dmg, m_ant_speed,m_color,starting,ending,m_attacking_paths[m_currently_attacking]);
    this->m_num_ants--;
    this->m_currently_attacking++;
    return tmp;
}

CRoad find_shortest_path(CNest *attacker, CNest *victim)
{
    coords tmp_start;
    coords tmp_end;

    double tmp_distance = __LONG_LONG_MAX__;

    for(auto i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            double cur_distance = attacker->m_entrypoints[i].distance(victim->m_entrypoints[j]);
            if(cur_distance < tmp_distance){
                tmp_distance = cur_distance;
                tmp_start = attacker->m_entrypoints[i];
                tmp_end = victim->m_entrypoints[j];
            }
        }
    }

    CRoad ret(tmp_start,tmp_end);
    return ret;
}

CSkillTree::CSkillTree(){
    m_nest_ptr = nullptr;
}

CSkillTree::CSkillTree(CNest * ptr){
    m_nest_ptr = ptr;
}



