#include "Player.h"

Player::Player(float hp, float attack, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float defense)
            :Unit(hp, attack, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height), defense(defense)
{
    icon_path = "://images/player_icon_test.png";
}

float Player::get_defense() const {
    return defense;
}

Player::State Player::get_state() const {
    return state;
}

void Player::user_controlled_movement(bool up, bool down, bool left, bool right) {
    if (up != down) {
        if (up) move_up(); else move_down();
    }

    if (left != right) {
        if (left) move_left(); else move_right();
    }
}

void Player::shoot() {
    int bullet_pos[2] = {pos_x, pos_y+height/2+bullet_size[1]/2};
    Bullet* new_shoot = new Bullet(bullet_size[0], bullet_size[1], bullet_pos[0], bullet_pos[1], bullet_velocity);
    if (fired_shoot == nullptr) {
        fired_shoot = new_shoot;
    } else {
        Bullet* last_shoot = fired_shoot;
//        while (last_shoot)
    }
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
