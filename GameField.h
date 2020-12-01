#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Player.h"
#include "Unit.h"
#include "Bullet.h"

// rendering display units and background here

class GameField : public QGraphicsScene {
    private:
        QList<QGraphicsPixmapItem*> hp_bar;

    public:
        GameField();
        void initial_render_unit(Unit* unit);
        void render_unit_update(Unit* unit);
        void remove_dead_unit_view(QGraphicsPixmapItem* view);

        void initial_render_bullet(Bullet* bullet, bool is_friendly);
        void render_bullet_update(QList<Bullet*>& bullet_list);

        void initial_render_player_hp(int MAX_HP);
        void render_player_hp_update();
};

#endif // GAMEFIELD_H
