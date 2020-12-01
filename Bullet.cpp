#include "Bullet.h"

#include <QDebug>

Bullet::Bullet(int width, int height, int pos_x, int pos_y, int velocity): width(width), height(height), pos_x(pos_x), pos_y(pos_y), velocity(velocity) {}

int Bullet::get_width() const {
    return width;
}

int Bullet::get_height() const {
    return height;
}

int Bullet::get_velocity() const {
    return velocity;
}

int Bullet::get_pos_x() const {
    return pos_x;
}

int Bullet::get_pos_y() const {
    return pos_y;
}

QGraphicsPixmapItem* Bullet::get_view() const {
    return view;
}

QString Bullet::get_frienly_fire_icon_path() const {
    return frienly_fire_icon_path;
}

QString Bullet::get_enemy_fire_icon_path() const {
    return enemy_fire_icon_path;
}

void Bullet::move_up() {
    pos_y -= velocity;
}

void Bullet::register_view(QGraphicsPixmapItem* _view) {
    view = _view;
}
