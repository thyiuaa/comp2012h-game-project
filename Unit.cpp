#include "Unit.h"

Unit::Unit(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height)
        : hp(hp), velocity_x(velocity_x), velocity_y(velocity_y), pos_x(pos_x), pos_y(pos_y), shooting_interval(shooting_interval), MAX_HP(MAX_HP), width(width), height(height) {}

int Unit::get_hp() const {
    return hp;
}

int Unit::get_MAX_HP() const {
    return MAX_HP;
}

int Unit::get_width() const {
    return width;
}

int Unit::get_height() const {
    return height;
}

int Unit::get_velocity_x() const {
    return velocity_x;
}

int Unit::get_velocity_y() const {
    return velocity_y;
}

int Unit::get_pos_x() const {
    return pos_x;
}

int Unit::get_pos_y() const {
    return pos_y;
}

int Unit::get_shooting_interval() const {
    return shooting_interval;
}

QString Unit::get_icon_path() const {
    return icon_path;
}

QGraphicsPixmapItem* Unit::get_view() const {
    return view;
}

void Unit::register_view(QGraphicsPixmapItem* _view) {
    view = _view;
}

void Unit::update_cooldown() {
    if (shooting_cooldown != 0) {
        shooting_cooldown -= 1;
    }
}

bool Unit::take_damage() {
    if (hp == 0) return false;

    hp -= 1;
    if (hp == 0) {
        return true;
    } else {
        return false;
    }
}

void Unit::move_up() {
    if (pos_y-velocity_y < -height) return;
    pos_y -= velocity_y;
}

void Unit::move_down() {
    if (pos_y+velocity_y > 840+height) return;
    pos_y += velocity_y;
}

void Unit::move_right() {
    if (pos_x+velocity_x > 670+width) return;
    pos_x += velocity_x;
}

void Unit::move_left() {
    if (pos_x-velocity_x < -width) return;
    pos_x -= velocity_x;
}
