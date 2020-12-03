#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Player.h"
#include "Enemy.h"
#include "Unit.h"
#include "Bullet.h"

// rendering display units and background here

class GameField : public QGraphicsScene {
    private:
        QList<QGraphicsPixmapItem*> hp_bar;

    public:
        GameField();
        void initial_render_unit(Unit* unit);
        void render_player_pos_update(Player* player);

        void initial_render_bullet(Bullet* bullet, bool is_friendly);

        void initial_render_player_hp(int MAX_HP);
        void render_player_hp_update();

        template <typename T> // for bullet_list and enemy_list
            void render_removeable_item_pos_update(T& item_list) {
                if (!item_list.isEmpty()) {
                    for (typename T::iterator item = item_list.begin(); item != item_list.end(); /*inbody*/) {
                        if ((*item)->get_pos_y() == -(*item)->get_height()-10 || (*item)->get_pos_y() > 839) {
                            removeItem((*item)->get_view());
                            delete (*item)->get_view();
                            item = item_list.erase(item);
                        } else {
                            (*item)->get_view()->setOffset((*item)->get_pos_x(), (*item)->get_pos_y());
                            ++item;
                        }
                    }
                }
            }
};

#endif // GAMEFIELD_H
