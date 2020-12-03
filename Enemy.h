#ifndef ENEMY_H
#define ENEMY_H

#include "Unit.h"
#include "Bullet.h"

class Enemy: public Unit {
    protected:
        float shooting_chance;
        int enemy_score; // score will be rewarded if the player kills this enemy

    public:
        Enemy(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float shooting_chance, int enemy_score);
        ~Enemy() = default;

        float get_shooting_chance() const;
        int get_enemy_score() const;

        void update_pos();
        virtual Bullet* shoot() override; // nullptr if enemy is in cooldown, or did not shoot by chance
};

#endif
