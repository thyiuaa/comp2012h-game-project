#include <cstdlib>

#include "GameEngine.h"

void GameEngine::show_hp_bar(GameField& game_field) const {
    game_field.initial_render_player_hp(player->get_MAX_HP());
}

//make use of rand() in cstdlib
void GameEngine::spawn_enemy(GameField& game_field) {
    int MAX_HP = 2 + rand()%4;
    int hp = MAX_HP;
    int velocity_x = rand()%3 - 1;
    int velocity_y = 1 + rand()%2; //speed but not velocity
    int shooting_interval = 10 * (1 + rand()%3);
    int score;
    switch(MAX_HP){
        case 2: score = 1000; break;
        case 3: score = 2000; break;
        case 4: score = 3000; break;
        case 5: score = 3000 + rand()%3000; break;
    }
    score *= velocity_y;
    float chance = 0.5;
    int width = QPixmap("://images/enemy_icon_temp.png").width();
    int height = QPixmap("://images/enemy_icon_temp.png").height();
    int pos_x = rand()%600;
    int pos_y = 0;

    Enemy* enemy = new Enemy(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height, chance, score);
    game_field.initial_render_unit(enemy);
    enemy_list.append(enemy);
}

void GameEngine::spawn_player(GameField& game_field) {
    int MAX_HP = 10;
    int hp = MAX_HP;
    int velocity_x = 3;
    int velocity_y = 3;
    int shooting_interval = 20;
    int width = QPixmap("://images/player_icon_test.png").width();
    int height = QPixmap("://images/player_icon_test.png").height();
    int pos_x = 335-width/2;
    int pos_y = 820-height;

    player = new Player(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height);
    game_field.initial_render_unit(player);
}

void GameEngine::player_shoot(GameField &game_field) {
    Bullet* bullet = player->shoot();
    if (bullet != nullptr) {
        friendly_bullet_list << bullet;
        game_field.initial_render_bullet(bullet, true);
    }
}

void GameEngine::enemy_shoot(GameField& game_field){
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); ++enemy) {
            Bullet* bullet = (*enemy)->shoot();
            if(bullet != nullptr) {
                enemy_bullet_list.append(bullet);
                game_field.initial_render_bullet(bullet, false);
            }
        }
    }
}

void GameEngine::collision_detection(GameField& game_field) {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); /*in body*/) {
            bool enemy_removed = false;
            // enemy vs player
            if (collide((*enemy), player)) {
                unit_collide_delay += 1;
                if (unit_collide_delay%60 == 1){ // 1 hp deducted for each 0.6s
                    update_hp_bar = true;
                    if(player->take_damage()) {
                        game_field.remove_and_delete_view(player->get_view());
                        return;
                    }
                }
            }

            // friendly_bullet vs enemy
            if (!friendly_bullet_list.isEmpty()) {
                for (QList<Bullet*>::iterator bullet = friendly_bullet_list.begin(); bullet != friendly_bullet_list.end(); /*in body*/) {
                    if (collide((*enemy), (*bullet))) {
                        game_field.remove_and_delete_view((*bullet)->get_view());
                        bullet = friendly_bullet_list.erase(bullet);
                        if((*enemy)->take_damage()) {
                            total_score += (*enemy)->get_enemy_score();
                            update_score_bar = true;
                            game_field.remove_and_delete_view((*enemy)->get_view());
                            enemy = enemy_list.erase(enemy);
                            enemy_removed = true;
                            break;
                        }
                    } else {
                        ++bullet;
                    }
                }
            }
            if (!enemy_removed) ++enemy;
        }
    }

    // enemy_bullet vs player
    if (!enemy_bullet_list.isEmpty() && player != nullptr) {
        for (QList<Bullet*>::iterator bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end(); /*in body*/) {
            if (collide(player, (*bullet))) {
                game_field.remove_and_delete_view((*bullet)->get_view());
                bullet = enemy_bullet_list.erase(bullet);
                update_hp_bar = true;
                if(player->take_damage()) {
                    game_field.remove_and_delete_view(player->get_view());
                    return;
                }
            } else {
                ++bullet;
            }
        }
    }
}

bool GameEngine::game_over() const {
    if (total_score >= WINNING_SCORE || player->get_hp() == 0) return true;

    return false;
}

bool GameEngine::show_game_over_screen(GameField& game_field) {
//    delete player;
//    enemy_list.clear();
//    friendly_bullet_list.clear();
//    enemy_bullet_list.clear();
    game_field.clear();
    game_field.addPixmap(QPixmap("://images/bg.jpg"))->setZValue(-1);
    if(total_score >= WINNING_SCORE) {
        return true;
    } else {
        return false;
    }
}

void GameEngine::refresh_all_pos(bool up, bool down, bool left, bool right) {
    // units
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); ++enemy) {
            (*enemy)->update_pos();
        }
    }
    update_player_view = player->update_pos(up, down, left, right);

    // bullets
    if(!friendly_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = friendly_bullet_list.begin(); bullet != friendly_bullet_list.end(); ++bullet) {
            (*bullet)->move_up();
        }
    }
    if(!enemy_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end(); ++bullet) {
            (*bullet)->move_up();
        }
    }
}

void GameEngine::refresh_units_bullet_view(GameField& game_field) {
    game_field.render_enemy_bullet_pos_update(enemy_list);
    if (update_player_view) {
        game_field.render_player_pos_update(player);
        update_player_view = false;
    }
    game_field.render_enemy_bullet_pos_update(friendly_bullet_list);
    game_field.render_enemy_bullet_pos_update(enemy_bullet_list);
}

void GameEngine::refresh_all_units_cooldown() {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); ++enemy) {
            (*enemy)->update_cooldown();
        }
    }
    player->update_cooldown();
}

void GameEngine::refresh_score(QLabel* score_bar) {
    if (update_score_bar) {
        score_bar->setText(QString("Score: %1").arg(total_score));
        update_score_bar = false;
    }
}

void GameEngine::refresh_hp(GameField& game_field) {
    if (update_hp_bar) {
        game_field.render_player_hp_update();
        update_hp_bar = false;
    }
}

GameEngine::~GameEngine() {
    delete player;
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator enemy = enemy_list.begin(); enemy != enemy_list.end(); ++enemy) {
            delete (*enemy);
        }
    }
    if(!friendly_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = friendly_bullet_list.begin(); bullet != friendly_bullet_list.end(); ++bullet) {
            delete (*bullet);
        }
    }
    if(!enemy_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end(); ++bullet) {
            delete (*bullet);
        }
    }
}
