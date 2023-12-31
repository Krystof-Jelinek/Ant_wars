#include "CNest.h"

CNest::CNest(){
        m_health = 1000;
        m_produc_speed = 5;
        m_ant_dmg = 20;
        m_ant_health = 60;
        m_ant_speed = 3;
        m_color = 'Y';
    }

CNest::CNest(CCoordinates coordinates, char color){
    m_coordinates = coordinates;
    m_color = color;
    m_entrypoints[0] = coords(m_coordinates.m_x1,m_coordinates.m_y1 +1);
    m_entrypoints[1] = coords(m_coordinates.m_x2,m_coordinates.m_y1 +1);
    m_entrypoints[2] = coords(m_coordinates.m_x1 + 3,m_coordinates.m_y1);
    m_entrypoints[3] = coords(m_coordinates.m_x1 + 3,m_coordinates.m_y2);
}

void CNest::setcoordinates(int x1, int x2, int y1, int y2){
    m_coordinates = CCoordinates(x1,x2,y1,y2);
}

void CNest::set_ant_health(int value){
    if(value <= 0){
        throw std::logic_error("Ants health cant be set to negative or zero!");
    }
    m_ant_health = value;
}

void CNest::set_ant_speed(int value){
    if(value <= 0){
        throw std::logic_error("Ants speed cant be set to negative or zero!");
    }
    m_ant_speed = value;
}

void CNest::set_ant_dmg(int value){
    if(value <= 0){
        throw std::logic_error("Ants dmg cant be set to negative or zero!");
    }
    m_ant_dmg = value;
}

void CNest::set_product_speed(int value){
    if(value <= 0){
        throw std::logic_error("Production speed cant be negative or zero");
    }
    m_produc_speed = value;
}

void CNest::set_sup_boost(bool input){
    m_ant_sup_boost = input;
}

void CNest::set_exploding(bool input){
    exploding_ants = input;
}

void CNest::set_flying(bool input){
    flying_ants = input;
}

bool CNest::is_flying(){
    return flying_ants;
}

char CNest::first_ant_num() const {
    return char(m_num_ants%10 + '0');
}

char CNest::second_ant_num() const {
    return char((floor(m_num_ants /10.0)) + '0');
}

void CNest::state_update(int tick){
    m_tree.make_effect();
    
    if(tick%m_produc_speed == 0){
        if(m_color == 'Y'){
            return;
        }
        m_num_ants++;
    }
}

void CNest::add_skill(shared_ptr<CSkill> src){
    m_tree.m_skills.push_back(src);
}

bool CNest::already_has_skill(const string & name){
    for(auto itr = m_tree.m_skills.begin(); itr != m_tree.m_skills.end(); itr++){
        if((*itr).get()->m_skill_name == name){
            return true;
        }
    }
    return false;
}

bool CNest::create_ant_check(int tick){
    if(m_attacking_paths.empty()){
        return false;
    }

    if(m_currently_attacking_num == 0){
        return false;
    }

    if(m_num_ants <= 0){
        return false;
    }
    
    if(tick % m_send_speed == 0){
        return true;
    }
    return false;
}

coords CNest::get_starting_coords(){
    switch(m_currently_attacking){
        case 0:
            if(this->m_coordinates.includes(m_attacking_paths[0].get()->m_begin)){
                return m_attacking_paths[0].get()->m_begin;
            }
            else{
                return m_attacking_paths[0].get()->m_end;
            }
            break;
        case 1:
            if(this->m_coordinates.includes(m_attacking_paths[1].get()->m_begin)){
                return m_attacking_paths[1].get()->m_begin;
            }
            else{
                return m_attacking_paths[1].get()->m_end;
            }
            break;
        case 2:
            if(this->m_coordinates.includes(m_attacking_paths[2].get()->m_begin)){
                return m_attacking_paths[2].get()->m_begin;
            }
            else{
                return m_attacking_paths[2].get()->m_end;
            }
            break;
        case 3:
            if(this->m_coordinates.includes(m_attacking_paths[3].get()->m_begin)){
                return m_attacking_paths[3].get()->m_begin;
            }
            else{
                return m_attacking_paths[3].get()->m_end;
            }
            break;            
    }

    throw invalid_argument("Mistake in getting starting coordinates for ant!");
}

shared_ptr<CAnt> CNest::create_ant(){

    if(m_currently_attacking == m_currently_attacking_num){
        m_currently_attacking = 0;
    }

    coords starting = get_starting_coords();

    coords ending;
    if(starting.distance(m_attacking_paths[m_currently_attacking].get()->m_end) < starting.distance(m_attacking_paths[m_currently_attacking].get()->m_begin)){
        ending = m_attacking_paths[m_currently_attacking].get()->m_begin;
    }
    else{
        ending = m_attacking_paths[m_currently_attacking].get()->m_end;
    }

    if(exploding_ants){
        auto tmp = make_shared<CExplodingAnt>(m_ant_health, m_ant_dmg, m_ant_speed,m_color,m_ant_sup_boost,starting,ending,m_attacking_paths[m_currently_attacking]);
        this->m_num_ants--;
        this->m_currently_attacking++;
        return tmp;
    }

    auto tmp = make_shared<CAnt>(m_ant_health, m_ant_dmg, m_ant_speed,m_color,m_ant_sup_boost,starting,ending,m_attacking_paths[m_currently_attacking]);
    this->m_num_ants--;
    this->m_currently_attacking++;
    return tmp;
}

CRoad find_shortest_path(CNest *attacker, CNest *victim)
{
    coords tmp_start;
    coords tmp_end;

    double tmp_distance = __LONG_LONG_MAX__;

    for(auto i = 0; i < 4;i++){
        for(int j = 0; j < 4;j++){
            double cur_distance = attacker->m_entrypoints[i].distance(victim->m_entrypoints[j]);
            if(cur_distance < tmp_distance){
                tmp_distance = cur_distance;
                tmp_start = attacker->m_entrypoints[i];
                tmp_end = victim->m_entrypoints[j];
            }
        }
    }

    CRoad ret(tmp_start,tmp_end);
    return ret;
}

//----------------------------------------------------------------------------------------

CSkillTree::CSkillTree(){
    m_nest_ptr = nullptr;
}

CSkillTree::CSkillTree(CNest * src){
    m_nest_ptr = src;
}

void CSkillTree::make_effect(){
    for(auto itr = m_skills.begin();itr != m_skills.end();itr++){
        (*itr)->affect_nest(m_nest_ptr);
    }
}

void CSkillTree::set_ptr(CNest * src){
    m_nest_ptr = src;
}

//----------------------------------------------------------------------------------------

CSkill::CSkill(const string & m_name, int cost){
    m_skill_name = m_name;
    m_cost = cost;
}

CFast_ant::CFast_ant(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CFast_ant::affect_nest(CNest * src){
    src->set_ant_speed(1);
}

CStrong_ant::CStrong_ant(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CStrong_ant::affect_nest(CNest * src){
    src->set_ant_health(80);
    src->set_ant_dmg(80);
}

CFast_rep::CFast_rep(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CFast_rep::affect_nest(CNest * src){
    src->set_product_speed(4);
}

CMore_sup::CMore_sup(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CMore_sup::affect_nest(CNest * src){
    src->set_sup_boost(true);
}

CExplo_ants::CExplo_ants(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CExplo_ants::affect_nest(CNest * src){
    src->set_exploding(true);
}

CFly_ants::CFly_ants(const string & m_name, int cost)
:CSkill(m_name,cost){}

void CFly_ants::affect_nest(CNest * src){
    src->set_flying(true);
}