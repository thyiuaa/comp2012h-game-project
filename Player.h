#include "Unit.h"

class Player : public Unit {
    
    public:
        enum State {ATTACK, DEFENSE};
        // constructor
        Player(float hp, float attack, int velocity[2], int pos[2], int shooting_interval, int MAX_HP, float defense);

        // accessor
        float get_defense() const;
        State get_state() const;

        virtual void shoot();
        virtual void take_damage(float raw_damage);

    private:
        float defense;
        State state {State::ATTACK};
};