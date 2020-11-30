#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "Bullet.h"

class Player : public Unit {
    
    public:
        enum State {ATTACK, DEFENSE};
        // constructor
        Player(float hp, float attack, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float defense);

        // accessor
        float get_defense() const;
        State get_state() const;

        void update_pos(bool up, bool down, bool left, bool right);

        virtual Bullet* shoot() override;
        virtual void take_damage(float raw_damage) override;

    private:
        float defense;
        State state {State::ATTACK};
        virtual ~Player() {};
};

#endif
