#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>

class Unit {
    protected:
        float hp;
        int width, height;
        float attack;
        int velocity_x, velocity_y;
        int pos_x, pos_y;
        int shooting_interval; // milisecond
        const int MAX_HP;
        int bullet_size[2]{1,1};
        int bullet_velocity{1};
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

        // pure virual funciton
        virtual void shoot() = 0; // player shoot when button pressed, enermy may shoot randomly 
        virtual void take_damage(float raw_damage) = 0; // player can reduce damage by defensing

        virtual ~Unit() {};
};

#endif
