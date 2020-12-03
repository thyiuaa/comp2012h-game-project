#include "Player.h"

Player::Player(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height)
            :Unit(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height)
{
    icon_path = "://images/player_icon_test.png";
}

bool Player::update_pos(bool up, bool down, bool left, bool right) {
    bool moved = false;
    if (up != down) {
        if (up) move_up(); else move_down();
        moved = true;
    }
    if (left != right) {
        if (left) move_left(); else move_right();
        moved = true;
    }
    return moved;
}

Bullet* Player::shoot() {
    if (shooting_cooldown != 0) return nullptr;

    int bullet_width = QPixmap("://images/friendly_fire.png").width();
    int bullet_height = QPixmap("://images/friendly_fire.png").height();
    int bullet_pos_x = pos_x+width/2-bullet_width/2;
    int bullet_pos_y = pos_y-0.75*bullet_height;
    int bullet_velocity = 2;
    Bullet* bullet = new Bullet(bullet_width, bullet_height, bullet_pos_x, bullet_pos_y, bullet_velocity);
    shooting_cooldown = shooting_interval;
    return bullet;
}
