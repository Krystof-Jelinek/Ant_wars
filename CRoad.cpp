
#include "CRoad.h"

CRoad::CRoad(coords begin, coords end){
        
        m_begin = begin;
        m_end = end;

        road.clear();
        road.push_back(begin);

        int x1 = begin.m_x;
        int y1 = begin.m_y;
        
        int x2 = end.m_x;
        int y2 = end.m_y;

        
        while(true){
            if((x1 == x2)&&(y1 == y2)){
                return;
            }

            int rise = y2-y1;
            int run = x2-x1;

            if(run == 0){
                if(y2 < y1){
                    y1--;
                    road.push_back(coords(x1,y1));
                    continue;
                }
                y1++;
                road.push_back(coords(x1,y1));
                continue;
            }
            else{
            float m = float(rise)/run;
            int b = y1 - int(round(m*x1));
            
            if((m <= 1)&&(m >= -1)){
                if(x2 < x1){
                    x1--;
                    y1 = int(round(m*x1 + b));
                    road.push_back(coords(x1,y1));
                    continue;
                }
                x1++;
                y1 = int(round(m*x1 + b));
                road.push_back(coords(x1,y1));
                continue;
            }
            else{
                if(y2 < y1){
                    y1--;
                    x1 = int(round((y1 - b) / m));
                    road.push_back(coords(x1,y1));
                    continue;
                }
                y1++;
                x1 = int(round((y1 - b) / m));
                road.push_back(coords(x1,y1));
                continue;
            }
        }

        }



    }

bool road_compare(CRoad & first, CRoad & second){
    if((first.m_begin == second.m_begin)&&(first.m_end == second.m_end)){
        return true;
    }

    if((first.m_begin == second.m_end)&&(first.m_end == second.m_begin)){
        return true;
    }

    return false;
}
