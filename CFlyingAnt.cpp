#include "CFlyingAnt.h"

CFlyingAnt::CFlyingAnt(int health, int dmg, int speed,char color,coords position, coords destiny_position, shared_ptr<CRoad> road)
    : CAnt(health, dmg, speed, color, position, destiny_position, road){}

bool CFlyingAnt::move(){
    return false;
}

void CFlyingAnt::attack(CAnt * victim){

}
    
void CFlyingAnt::affect_nest(){

}