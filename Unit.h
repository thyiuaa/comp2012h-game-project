#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>

#include "Bullet.h"

// ABC for Player and Enemy class
class Unit {
    protected:
        int hp;
        const int MAX_HP;
        int width, height; // pixel
        int velocity_x, velocity_y; // pixel per frame
        int pos_x, pos_y; //pixel
        int shooting_interval; // frame
        int shooting_cooldown {0}; // frame
        QString icon_path {"\0"};
        QGraphicsPixmapItem* view {nullptr};

    public:
        Unit(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height);
        virtual ~Unit() = default;

        int get_hp() const;
        int get_MAX_HP() const;
        int get_width() const;
        int get_height() const;
        int get_velocity_x() const;
        int get_velocity_y() const;
        int get_pos_x() const;
        int get_pos_y() const;
        int get_shooting_interval() const;
        QString get_icon_path() const;
        QGraphicsPixmapItem* get_view() const;

        void register_view(QGraphicsPixmapItem* _view);
        void update_cooldown(); // cooldown decrease by 1 per frame
        bool take_damage(); // true if the unit died after taking damage, otherwise false

        void move_up();
        void move_down();
        void move_right();
        void move_left();

        //player shoot when button pressed, enemy may shoot randomly
        virtual Bullet* shoot() = 0; // set shooting_cooldown to shooting interval and return the created bullet (can be nullptr)

};

#endif
