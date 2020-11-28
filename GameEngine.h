#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QList>
#include <QGraphicsScene>

#include "Unit.h"
#include "Player.h"
#include "Enemy.h"
#include "GameField.h"

// control game logic, i.e. units spawning, unit management, game start, game end
// play a role as the middleman between mainwindow and other things
class GameEngine {
    private:
        int total_score;
        Player* player;
        QList<Enemy*> enemy_list;
    public:
        GameEngine();

        int get_total_score() const;
        void game_start();
        bool game_over();
        void spawn_enemy();
        void spawn_player(GameField& game_gield, QGraphicsScene& scene);
        void update_score();
        void refresh_all_units_update(GameField& game_field);
        void send_player_move_to_unit(bool up, bool down, bool left, bool right);
};

#endif
