#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QList>
#include <QLabel>

#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "GameField.h"

// control game logic, i.e. units spawning, on hit event, game end
// play a role as the middleman between mainwindow and game component i.e. Player, Enemy, Bullet, and GameField
class GameEngine {
    private:
        const int WINNING_SCORE {100000};
        int total_score {0};
        Player* player {nullptr};
        QList<Enemy*> enemy_list;
        QList<Bullet*> friendly_bullet_list;
        QList<Bullet*> enemy_bullet_list;

        int enemy_spawn_timer {0}; // number of frames passed since the game start
        const int ENEMY_SPAWN_INTERVAL {150}; // number of frames between each enemy spawn
        int unit_collide_delay {0}; // number of frames that player collided with enemy
        const int UNIT_COLLIDE_DAMAGE_INTERVAL {60}; // number of frame between every time player takes collision damage with enemy

        bool update_player_view {false};
        bool update_score_bar {false};
        bool update_hp_bar {false};

    public:
        GameEngine() = default;
        ~GameEngine();

        void reset_total_score(QLabel* score_bar);
        void show_hp_bar(GameField& game_field) const;
        void spawn_enemy(GameField& game_field);
        void spawn_player(GameField& game_field);
        void player_shoot(GameField& game_field);
        void enemy_shoot(GameField& game_field);
        void collision_detection(GameField& game_field);
        bool game_over() const; // true if total_score > WINNING_SCORE or player died, otherwise false
        bool show_game_over_screen(GameField& game_field); // true if the player wins, otherwise false

        // functions for the screen refresher to call
        void refresh_all_pos(bool up, bool down, bool left, bool right);
        void refresh_units_bullet_view(GameField& game_field);
        void refresh_all_units_cooldown();
        void refresh_score(QLabel* score_bar);
        void refresh_hp(GameField& game_field);

        template <typename T1, typename T2> // for Player*, Enemy* and Bullet*
        bool collide(T1& obj1, T2& obj2) const { // return true if 2 objects collide with each other, otherwise false
            int obj1_left = obj1->get_pos_x(),                    obj1_top = obj1->get_pos_y();
            int obj2_left = obj2->get_pos_x(),                    obj2_top = obj2->get_pos_y();
            int obj1_right = obj1->get_pos_x()+obj1->get_width(), obj1_bottom = obj1->get_pos_y()+obj1->get_height();
            int obj2_right = obj2->get_pos_x()+obj2->get_width(), obj2_bottom = obj2->get_pos_y()+obj2->get_height();

            if (obj1_top < obj2_top) { // smaller is higher
                if (obj1_bottom >= obj2_top) { // any part of obj1 is at the vertical level of obj2
                    if (((obj2_left < obj1_right) && (obj2_left > obj1_left)) || ((obj2_right < obj1_right) && (obj2_right > obj1_left))) { // left or right end of obj2 is in obj1
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                if (obj2_bottom >= obj1_top) {
                    if (((obj1_left < obj2_right) && (obj1_left > obj2_left)) || ((obj1_right < obj2_right) && (obj1_right > obj2_left))) {
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
