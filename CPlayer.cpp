#include "CPlayer.h"


CPlayer::CPlayer(char color){
    dna_points = 0;
    dna_produc_speed = 10;
    m_color = color;
}

void CPlayer::update_state(int tick){
    if(tick % dna_produc_speed == 0){
        dna_points++;
    }
}

void CPlayer::add_nest(CNest * src){
    this->players_nests.push_back(src);
}


