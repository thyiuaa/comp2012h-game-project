#include "Player.h"

Player::Player(float hp, float attack, int velocity[2], int pos[2], int shooting_interval, int MAX_HP, float defense):
    defense(defense), Unit(hp, attack, velocity, pos, shooting_interval, MAX_HP) {}

float Player::get_defense() const {
    return defense;
}

Player::State Player::get_state() const {
    return state;
}

void Player::shoot() {
}

void Player::take_damage(float raw_damage) {
    float expected_hp = 0;
    if (state == State::ATTACK) {
        expected_hp = hp-raw_damage;
    } else {
        expected_hp = hp-(raw_damage-(defense*hp/MAX_HP));
    }

    if (expected_hp < 0) {
        hp = 0;
    }
}