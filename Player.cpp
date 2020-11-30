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

void Player::update_pos(bool up, bool down, bool left, bool right) {
    if (up != down) {
        if (up) move_up(); else move_down();
    }

    if (left != right) {
        if (left) move_left(); else move_right();
    }
}

Bullet* Player::shoot() {
    int bullet_width = QPixmap("://images/friendly_fire.png").width();
    int bullet_height = QPixmap("://images/friendly_fire.png").height();
    int bullet_pos_x = pos_x+width/2-bullet_width/2;
    int bullet_pos_y = pos_y-0.75*bullet_height;
    int bullet_velocity = 1;

    if (shooting_cooldown == 0) {
        Bullet* bullet = new Bullet(bullet_width, bullet_height, bullet_pos_x, bullet_pos_y, bullet_velocity);
        shooting_cooldown = shooting_interval;
        return bullet;
    }
    return nullptr;
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
