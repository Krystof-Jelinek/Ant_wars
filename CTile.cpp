
#include <iostream>
#include "CTile.h"

#define RESET "\033[0m"
#define GREENSQR "\033[42m \033[0m"
#define REDSQR "\033[43m \033[0m"
#define BLUESQR "\033[44m \033[0m"
#define GREYSQR "\033[100m \033[0m"

#define GREEN "\033[32m"
#define RED "\033[33m"
#define BLUE "\033[34m"
#define GREY "\033[90m"

using namespace std;

CTile::CTile(){
    m_char = ' ';
    m_color = 'W';
    m_is_wall = false;
    m_ant_ocup = nullptr;
    m_nest_ocup = nullptr;
}

void CTile::set_char(char src){
    m_char = src;
}

void CTile::set_color(char src){
    if((src != 'W')&&(src != 'G')&&(src != 'R')&&(src != 'B')&&(src != 'Y')){
        throw invalid_argument("Non Existing Color !");
    }
    m_color = src;
}    

void CTile::set_selection_char(char src){
    if(this->m_ant_ocup != nullptr){
        return;
    }
    this->set_char(src);
}

void CTile::print_color_block(){
    if(m_color == 'R'){
        cout << REDSQR;
    }
    if(m_color == 'B'){
        cout << BLUESQR;
    }
    if(m_color == 'G'){
        cout << GREENSQR;
    }
    if(m_color == 'Y'){
        cout << GREYSQR;
    }
}

void CTile::print_color_char(){
    if(m_color == 'R'){
        cout << RED << m_char << RESET;
    }
    if(m_color == 'B'){
        cout << BLUE << m_char << RESET;
    }
    if(m_color == 'G'){
        cout << GREEN << m_char << RESET;
    }
    if(m_color == 'Y'){
        cout << GREY << m_char << RESET;
    }
}

void CTile::print_tile(){
    if(m_color == 'W'){
        cout << m_char;
        return;
    }
    if((m_char == ' ')){
        print_color_block();
        return;
    }
    else{
        print_color_char();
        return;
    }
}

void CTile::reset_tile(){

    if(m_is_wall){
        m_color = 'W';
        m_char = '#';
        m_ant_ocup = nullptr;
        m_nest_ocup = nullptr;
        return;
    }

    m_color = 'W';
    m_char = ' ';
    m_ant_ocup = nullptr;
    m_nest_ocup = nullptr;
}
