#include "CExplodingAnt.h"

CExplodingAnt::CExplodingAnt(int health, int dmg, int speed,char color,coords position, coords destiny_position, shared_ptr<CRoad> road)
    : CAnt(health, dmg, speed, color, position, destiny_position, road){}


void CExplodingAnt::attack(CAnt * victim){

} 

void CExplodingAnt::affect_nest(){
    
}

bool CExplodingAnt::move(){
    return false;
}
