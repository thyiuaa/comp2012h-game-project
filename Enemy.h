#ifndef ENEMY_H
#define ENEMY_H

#include "Unit.h"
#include "Bullet.h"

class Enemy: public Unit {
    protected:
        float shooting_chance;
        int enemy_score;
    public:
        //constructor
        Enemy(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float shooting_chance, int enemy_score);

        //accessor
        float get_shooting_chance();
        int get_enemy_score();

        //idk what these are called
        virtual Bullet* shoot();
};

#endif
