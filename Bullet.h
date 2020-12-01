#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class Bullet {
    private:
        int width, height, pos_x, pos_y, velocity;
    public:
        QString frienly_fire_icon_path {"://images/friendly_fire.png"};
        QString enemy_fire_icon_path {"://images/enemy_fire.png"};
    
    private:
        friend class Player;
        QGraphicsPixmapItem* view;

    public:
        Bullet(int width, int height, int pos_x, int pos_y, int velocity);
        int get_width() const;
        int get_height() const;
        int get_velocity() const;
        int get_pos_x() const;
        int get_pos_y() const;
        QGraphicsPixmapItem* get_view() const;
        QString get_frienly_fire_icon_path() const;
        QString get_enemy_fire_icon_path() const;

        void move_up();
        void register_view(QGraphicsPixmapItem* _view);
};

#endif
