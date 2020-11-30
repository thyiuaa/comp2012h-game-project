#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>

#include "Bullet.h"

class Unit {
    protected:
        float hp;
        const int MAX_HP;
        float attack;
        int width, height; // pixel

        int velocity_x, velocity_y; // pixel per frame
        int pos_x, pos_y; //pixel

        int shooting_interval; // frame
        int shooting_cooldown{0}; // frame

        QGraphicsPixmapItem* view;
        QString icon_path;

    public:
        // constructer
        Unit(float hp, float attack, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height);

        // accessor
        float get_hp() const;
        float get_attack() const;
        int get_velocity_x() const;
        int get_velocity_y() const;
        int get_pos_x() const;
        int get_pos_y() const;
        int get_shooting_interval() const;
        int get_width() const;
        int get_height() const;
        QString get_icon_path() const;
        QGraphicsPixmapItem* get_view() const;

        // mutator
        void move_up();
        void move_down();
        void move_right();
        void move_left();
        void register_view(QGraphicsPixmapItem* _view);
        void update_cooldown();

        // pure virual funciton
        virtual Bullet* shoot() = 0; // player shoot when button pressed, enermy may shoot randomly
        virtual void take_damage(float raw_damage) = 0; // player can reduce damage by defensing

        virtual ~Unit() {};
};

#endif
