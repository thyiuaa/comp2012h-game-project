#include <QDebug>

#include "GameEngine.h"

GameEngine::GameEngine()
{

}

void GameEngine::show_hp_bar(GameField& game_field) const {
    game_field.initial_render_player_hp(player->get_MAX_HP());
}

void GameEngine::spawn_player(GameField& game_field) {
    int hp = 10;
    int velocity_x = 3;
    int velocity_y = 2;
    int shooting_interval = 20;
    int MAX_HP = 10;
    int width = QPixmap("://images/player_icon_test.png").width();
    int height = QPixmap("://images/player_icon_test.png").height();
    int pos_x = 335-width/2;
    int pos_y = 820-height;
    float defense = 1;

    player = new Player(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height, defense);
    game_field.initial_render_unit(player);
}

bool GameEngine::game_over() {
    if (total_score > 100 || player->get_hp() == 0) return true;

    return false;
}

void GameEngine::player_shoot(GameField &game_field) {
    Bullet* bullet = player->shoot();
    if (bullet != nullptr) {
        friendly_bullet_list << bullet;
        game_field.initial_render_bullet(bullet, true);
    }
}

void GameEngine::refresh_units_bullet_view(GameField& game_field) {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            int dummy = 0;
        }
    }
    if (update_player_view) {
        game_field.render_unit_update(player);
        update_player_view = false;
    }
    game_field.render_bullet_update(friendly_bullet_list);
    game_field.render_bullet_update(enemy_bullet_list);
}

void GameEngine::refresh_all_units_cooldown() {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            int dummy = 0;
        }
    }
    player->update_cooldown();
}

void GameEngine::refresh_all_pos(bool up, bool down, bool left, bool right) {
    // units
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            int dummy = 0;
        }
    }
    update_player_view = player->update_pos(up, down, left, right);

    // bullets
    if(!friendly_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator i = friendly_bullet_list.begin(); i != friendly_bullet_list.end(); ++i) {
            (*i)->move_up();
        }
    }
    if(!enemy_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator i = enemy_bullet_list.begin(); i != enemy_bullet_list.end(); ++i) {
            (*i)->move_up();
        }
    }
}

void GameEngine::collision_detection(GameField& game_field) {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); ++enemy) {
            // friendly_bullet vs enemy
            if (!friendly_bullet_list.isEmpty()) {
                for (QList<Bullet*>::iterator bullet = friendly_bullet_list.begin(); bullet != friendly_bullet_list.end(); ++bullet) {
                    if (collide((*enemy), (*bullet))) {
                        int dummy = 0;
                    }
                }
            }

            // enemy vs player
            if (collide((*enemy), player)) {
                int dummy = 0;
            }
        }
    }

    // enemy_bullet vs player
    if (!enemy_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end(); ++bullet) {
            if (collide(player, (*bullet))) {
                update_hp_bar = true;
                if(player->take_damage()) {
                    game_field.remove_dead_unit_view(player->get_view());
                }
            }
        }
    }
}

void GameEngine::refresh_hp(GameField& game_field) {
    if (update_hp_bar) {
        game_field.render_player_hp_update();
        update_hp_bar = false;
    }
}

void GameEngine::refresh_score(QLabel* score_bar) {
    if (update_score_bar) {
        score_bar->setText(QString("Score: %1").arg(total_score));
        update_score_bar = false;
    }
}
