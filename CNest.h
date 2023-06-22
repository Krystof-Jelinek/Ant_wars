#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include "CCoordinates.h"
#include "CAnt.h"
#include "CRoad.h"
#include "CSkill.h"

//#include "CSkillTree.h"

using namespace std;

class CNest;


class CSkill{
    public:
    string m_skill_name;
    int m_cost;

    CSkill(string & m_name, int cost);
    virtual void affect_nest(CNest * src) = 0;
};

class CFast_rep : public CSkill{
    public:
    CFast_rep(string & m_name, int cost);
    void affect_nest(CNest * src) override;
};

class CFast_ant : public CSkill{
    public:
    CFast_ant(string & m_name, int cost);
    void affect_nest(CNest * src) override;
};

class CMore_sup : public CSkill{
    public:
    CMore_sup(string & m_name, int cost);
    void affect_nest(CNest * src) override;
};

class CStrong_ant : public CSkill{
    public:
    CStrong_ant(string & m_name, int cost);
    void affect_nest(CNest * src) override;
};

class CSkillTree{
    private:
    
    CNest * m_nest_ptr;

    public:
    vector<shared_ptr<CSkill>> m_skills;

    CSkillTree();
    CSkillTree(CNest * src);

    void set_ptr(CNest * src);
    void make_effect();

};


class CNest{
    private:
    
    //basic stats of the nest
    int m_health = 1500;
    int m_produc_speed = 6;
    int m_send_speed = 3;
    
    //basic values for the produced ant, these will change with buffs
    int m_ant_health = 40;
    int m_ant_dmg = 40;
    int m_ant_speed = 2;
    bool m_ant_sup_boost = false;


    public:
    char m_color = 'Y';
    int m_num_ants = 0;
    int m_currently_attacking = 0;
    int m_currently_attacking_num = 0;

    CSkillTree m_tree;
    CCoordinates m_coordinates;
    vector<shared_ptr<CRoad>> m_connected_paths;
    vector<shared_ptr<CRoad>> m_attacking_paths;
    coords m_entrypoints[4];
    
    CNest();

    CNest(CCoordinates coordinates, char color);

    void setcoordinates(int x1, int x2, int y1, int y2);

    void set_ant_health(int value);

    void set_ant_speed(int value);

    void set_ant_dmg(int value);

    void set_product_speed(int value);

    void set_sup_boost(bool input);

    char first_ant_num() const ;

    char second_ant_num() const ;

    void state_update(int tick);

    void add_skill(shared_ptr<CSkill> src);

    bool already_has_skill(const string & name);

    bool create_ant_check(int tick);

    coords get_starting_coords();

    CAnt create_ant();

};

CRoad find_shortest_path(CNest * attacker, CNest * victim);