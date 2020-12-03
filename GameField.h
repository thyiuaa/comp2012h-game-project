#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Player.h"
#include "Unit.h"
#include "Bullet.h"

// Inherited from QGraphicsScene
// for rendering the display for player, enemy and bullet
class GameField : public QGraphicsScene {
    private:
        QList<QGraphicsPixmapItem*> hp_bar;

    public:
        GameField() = default;
        ~GameField() = default;

        void initial_render_player_hp(int MAX_HP);
        void render_player_hp_update();

        void initial_render_unit(Unit* unit);
        void initial_render_bullet(Bullet* bullet, bool from_player);
        void render_player_pos_update(Player* player);

        template <typename T> // for QList<Bullet*> and QList<Enemy*>
        void render_enemy_bullet_pos_update(T& item_list) { // remove out of bound bullet and enemy
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

        void remove_and_delete_view(QGraphicsPixmapItem* view);
};

#endif // GAMEFIELD_H
