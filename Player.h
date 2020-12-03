#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "Bullet.h"

// user controlled character
class Player : public Unit {
    public:
        Player(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height);
        ~Player() = default;

        bool update_pos(bool up, bool down, bool left, bool right); // parameters are user's keypress
        virtual Bullet* shoot() override; // nullptr if player is in cooldown
};

#endif
