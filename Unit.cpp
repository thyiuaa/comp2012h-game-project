#include "Unit.h"

Unit::Unit(float hp, float attack, int velocity[2], int pos[2], int shooting_interval, int MAX_HP): hp(hp), attack(attack), shooting_interval(shooting_interval), MAX_HP(MAX_HP) {
    this->velocity[0] = velocity[0];
    this->velocity[1] = velocity[1];
    this->pos[0] = pos[0];
    this->pos[1] = pos[1];
}

float Unit::get_hp() const {
    return hp;
}

float Unit::get_attack() const {
    return attack;
}

// TODO: return a pointer
int* Unit::get_velocity() const {
    return velocity;
}

int* Unit::get_pos() const {
    return pos;
}

int Unit::get_shooting_interval() const {
    return shooting_interval;
}

// in bound validation should be done by game engine
void Unit::move_up() {
    pos[1] += velocity[1];
}

void Unit::move_down() {
    pos[1] -= velocity[1];
}

void Unit::move_right() {
    pos[0] += velocity[0];
}

void Unit::move_left() {
    pos[0] -= velocity[0];
}