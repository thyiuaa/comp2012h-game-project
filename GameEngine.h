#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QList>
#include <QLabel>

#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "GameField.h"

// control game logic, i.e. units spawning, unit management, game start, game end
// play a role as the middleman between mainwindow and other things
class GameEngine {
    private:
        int total_score {0};
        Player* player;
        QList<Enemy*> enemy_list;
        QList<Bullet*> friendly_bullet_list;
        QList<Bullet*> enemy_bullet_list;

//        bool update_hp{false};
        bool update_player_view{false};
        bool update_score_bar{false};
        bool update_hp_bar {false};

    public:
        GameEngine();

        int get_total_score() const;

        void show_hp_bar(GameField& game_field) const;

        void spawn_enemy(GameField& game_field);
        void spawn_player(GameField& game_field);
        void player_shoot(GameField& game_field);
        void enemy_shoot(GameField& game_field);
        void collision_detection(GameField& game_field);
        bool game_over();
        bool game_over_refresh(GameField& game_field);

        void refresh_all_pos(bool up, bool down, bool left, bool right);
        void refresh_units_bullet_view(GameField& game_field);
        void refresh_all_units_cooldown();
        void refresh_score(QLabel* score_bar);
        void refresh_hp(GameField& game_field);

        // objn's left end = objn->get_pos_x()
        // objn's right end = objn->get_pos_x()+objn->get_width()
        // objn's top = objn->get_pos_y()
        // objn's bottom = objn->get_pos_y()+objn->get_height()
        template <typename T1, typename T2> // for player*, enemy* and bullet*
            bool collide(T1& obj1, T2& obj2) {
                if (obj1->get_pos_y() < obj2->get_pos_y()) {
                    if (obj1->get_pos_y()+obj1->get_height() >= obj2->get_pos_y()) { // any part of obj1 is at the vertical level of obj2
                        if (((obj2->get_pos_x()<obj1->get_pos_x()+obj1->get_width()) && (obj2->get_pos_x()>obj1->get_pos_x()))
                            || ((obj2->get_pos_x()+obj2->get_width()<obj1->get_pos_x()+obj1->get_width()) && (obj2->get_pos_x()+obj2->get_width()>obj1->get_pos_x()))) { // left or right end of obj2 is in obj1
                            return true;
                        } else {
                            return false;
                        }
                    }
                } else {
                    if (obj2->get_pos_y()+obj2->get_height() >= obj1->get_pos_y()) {
                        if (((obj1->get_pos_x()<obj2->get_pos_x()+obj2->get_width()) && (obj1->get_pos_x()>obj2->get_pos_x()))
                            || ((obj1->get_pos_x()+obj1->get_width()<obj2->get_pos_x()+obj2->get_width()) && (obj1->get_pos_x()+obj1->get_width()>obj2->get_pos_x()))) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
                return false;
            }
};

#endif
