#pragma once

#include <iostream>
#include <cmath>

using namespace std;

struct coords{
    int m_x;
    int m_y;

    coords();
    coords(int x, int y);

    double distance(const coords & sec){
        return sqrt(pow((this->m_x - sec.m_x),2) + pow((this->m_y - sec.m_y),2));
    }

    bool operator==(const coords & sec);

    bool operator!=(const coords & sec);


};

class CCoordinates{
    public:
    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;

    CCoordinates();

    CCoordinates(int x1, int x2, int y1, int y2);

    bool includes(const coords & src);
};