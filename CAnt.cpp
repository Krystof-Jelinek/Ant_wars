#include "CAnt.h"

CAnt::CAnt(){
    m_health = 60;
    m_dmg = 20;
    m_speed = 3;
    m_road = nullptr;
    m_support_boost = false;
}

CAnt::CAnt(int health, int dmg, int speed,char color,bool sup_boost,coords position, coords destiny_position, shared_ptr<CRoad> road){
    m_health = health;
    m_dmg = dmg;
    m_speed = speed;
    m_position = position;
    m_destiny_coords = destiny_position;
    m_color = color;
    m_road = road;
    m_support_boost = sup_boost;
}

void CAnt::set_destiny_coords(const coords & src ){
    m_destiny_coords = src;
}

bool CAnt::update_map_state(int tick){
    
    if(tick%m_speed == 0){
        return this->move();
    }
    return false;
}

bool CAnt::move(){

    for(auto itr = m_road->road.begin();itr != m_road->road.end();itr++){
        if((*itr) != m_position){
            continue;
        }

        if(itr == m_road->road.begin()){
            itr++;
            m_position = (*itr);
            return false; 
        }

        itr++;
        auto next_itr = itr;
        itr --;
        itr--;
        auto prev_itr = itr;
        itr++;

        //compare whether the distanec from my destination is gettin longer or shorter and by that criteria the path is picked for the ant
        if(next_itr == m_road->road.end()){
            m_position = (*prev_itr);
            return false;
        }

        if((*prev_itr).distance(m_destiny_coords) < (*next_itr).distance(m_destiny_coords)){
            m_position = (*prev_itr);
            return false;
        }
        else{
            m_position = (*next_itr);
            return false;
        }

    }
    return true;
}


void CAnt::attack(CAnt * victim){
    victim->m_health = victim->m_health - this->m_dmg;
}

void CAnt::affect_nest(){

}
