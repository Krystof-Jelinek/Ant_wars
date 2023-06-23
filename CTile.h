#pragma once

#include <iostream>
#include "CNest.h"
#include "CAnt.h"

using namespace std;

class CTile{
    private:
    char m_char;
    char m_color;
    
    public:
    shared_ptr<CAnt> m_ant_ocup;
    CNest * m_nest_ocup;

    void set_char(char src);
    
    void set_color(char src);

    void set_selection_char(char src);
    
    CTile();

    void print_color_block();

    void print_color_char();

    void print_tile();

    void reset_tile();

    bool is_wall();

};