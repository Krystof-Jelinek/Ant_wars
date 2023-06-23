#include "CFlyingAnt.h"

CFlyingAnt::CFlyingAnt(int health, int dmg, int speed,char color, bool sup,coords position, coords destiny_position, shared_ptr<CRoad> road)
    : CAnt(health, dmg, speed, color, sup, position, destiny_position, road){}

bool CFlyingAnt::move(){
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
    
void CFlyingAnt::affect_nest(){

}