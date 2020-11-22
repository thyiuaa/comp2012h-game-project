#include "Unit.h"

class Enemy: public Unit {
    protected:
        float shooting_chance;
        int enemy_score;
    public:
        //constructor
        Enemy(float hp, float attack, int velocity[2], int pos[2], int shooting_interval, int MAX_HP, float shooting_chance, int enemy_score);

        //accessor
        float get_shooting_chance();
        int get_enemy_score();

        //idk what these are called
        virtual void shoot();
        virtual void take_damage(float raw_damage);
};