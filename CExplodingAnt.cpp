#include "CExplodingAnt.h"

CExplodingAnt::CExplodingAnt(int health, int dmg, int speed,char color, bool sup,coords position, coords destiny_position, shared_ptr<CRoad> road)
    : CAnt(health, dmg, speed, color, sup ,position, destiny_position, road){}


void CExplodingAnt::attack(CAnt * victim){
    victim->m_health = 0;
    this->m_health = 0;
} 

void CExplodingAnt::affect_nest(){
    
}

bool CExplodingAnt::move(){
    return false;
}
