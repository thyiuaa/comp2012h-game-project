#include "Unit.h"

Unit::Unit(float hp, float attack, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height)
        : hp(hp), attack(attack), velocity_x(velocity_x), velocity_y(velocity_y), pos_x(pos_x), pos_y(pos_y), shooting_interval(shooting_interval), MAX_HP(MAX_HP), width(width), height(height) {}

float Unit::get_hp() const {
    return hp;
}

float Unit::get_attack() const {
    return attack;
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

int Unit::get_width() const {
    return width;
}

int Unit::get_height() const {
    return height;
}

QString Unit::get_icon_path() const {
    return icon_path;
}

QGraphicsPixmapItem* Unit::get_view() const {
    return view;
}

// in bound validation should be done by game engine
// top left corner is (0,0)
void Unit::move_up() {
    pos_y -= velocity_y;
}

void Unit::move_down() {
    pos_y += velocity_y;
}

void Unit::move_right() {
    pos_x += velocity_x;
}

void Unit::move_left() {
    pos_x -= velocity_y;
}

void Unit::register_view(QGraphicsPixmapItem* _view) {
    view = _view;
}
