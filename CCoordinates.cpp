#include "CCoordinates.h"

CCoordinates::CCoordinates(){
    m_x1 = -5;
    m_x2 = -5;
    m_y1 = -5;
    m_y2 = -5;
}

CCoordinates::CCoordinates(int x1, int x2, int y1, int y2){
    m_x1 = x1;
    m_x2 = x2;
    m_y1 = y1;
    m_y2 = y2;
}

bool CCoordinates::includes(const coords & src){
    int x = src.m_x;
    int y = src.m_y;

    for(int i = this->m_x1;i <= this->m_x2;i++){
        for(int j = this->m_y1;j <= this->m_y2;j++){
            if((i == x)&&(j == y)){
                return true;
            }
        }
    }
    return false;
}

coords::coords(){
    m_x = 0;
    m_y = 0;
}


coords::coords(int x, int y){
    m_x = x;
    m_y = y;
}

bool coords::operator==(const coords & sec){
    if((this->m_x == sec.m_x)&&(this->m_y == sec.m_y)){
    return true;
    }
    return false;
}

bool coords::operator!=(const coords & sec){
    if((this->m_x == sec.m_x)&&(this->m_y == sec.m_y)){
        return false;
    }
        return true;
}