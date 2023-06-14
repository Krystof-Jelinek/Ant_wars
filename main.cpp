#include <iostream>
#include <cassert>
#include "CNest.h"
#include "CAnt.h"
#include "CMap.h"
#include "CRoad.h"



int main(void){
    
    CMap mapa;
    
    CNest green(CCoordinates(10,16,20,22),'G');
    CNest red(CCoordinates(20,26,6,8),'R');
    
    CNest gray(CCoordinates(40,46,3,5),'Y');
    CNest green2(CCoordinates(50,56,25,27),'G');

    mapa.add_nest(green);
    mapa.add_nest(red);
    //mapa.add_nest(gray);
    mapa.add_nest(green2);

    //mapa.setwall(coords(0,15),coords(20,15));

    mapa.attack(&(mapa.all_nests[2]),&(mapa.all_nests[0]));
    mapa.attack(&(mapa.all_nests[0]),&(mapa.all_nests[2]));



    mapa.m_selected_nest = &(mapa.all_nests[0]);

    int tick = 1;
    mapa.printmap();

    while(1){

        char c = getchar();
        if(c == 'q'){
            break;
        }
        if(c == 'n'){
            mapa.select_next_nest();
            mapa.printmap();
            continue;
        }
        mapa.update_map(tick);
        
        mapa.printmap();
        tick++;
    }
    
    return 0;
}