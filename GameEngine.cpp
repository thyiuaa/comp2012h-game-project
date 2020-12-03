#include <QDebug>
#include <cstdlib>

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

//make use of rand() in cstdlib
void GameEngine::spawn_enemy(GameField& game_field){
    int hp = 2 + rand()%4;
    int velocity_x = rand()%3 - 1;
    int velocity_y = 1 + rand()%2; //speed but not velocity
    int shooting_interval = 10 * (1 + rand()%3);
    int MAX_HP = hp;
    int score;
    switch(MAX_HP){
    case 2: score = 1; break;
    case 3: score = 2; break;
    case 4: score = 3; break;
    case 5: score = 3 + rand()%3; break;
    }
    score *= velocity_y;
    float chance = 0.5;
    int width = QPixmap("://images/enemy_icon_temp.png").width();
    int height = QPixmap("://images/enemy_icon_temp.png").height();
    int pos_x = rand()%570;
    int pos_y = 0;
    Enemy* enemy = new Enemy(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height, chance, score);
    game_field.initial_render_unit(enemy);
    enemy_list.append(enemy);
    qDebug() << enemy_list;
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

void GameEngine::enemy_shoot(GameField& game_field){
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            Bullet* bullet = (*i)->shoot();
            if(bullet != nullptr){
                enemy_bullet_list.append(bullet);
                game_field.initial_render_bullet(bullet, false);
            }
        }
    }
}

void GameEngine::refresh_units_bullet_view(GameField& game_field) {
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            game_field.render_unit_update(*i);
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
            (*i)->update_cooldown();
        }
    }
    player->update_cooldown();
}

void GameEngine::refresh_all_pos(bool up, bool down, bool left, bool right) {
    // units
    if(!enemy_list.isEmpty()) {
        for (QList<Enemy*>::iterator i = enemy_list.begin(); i != enemy_list.end(); ++i) {
            (*i)->update_pos();
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
                        delete (*bullet)->get_view();
                        friendly_bullet_list.removeOne(*bullet);
                        if((*enemy)->take_damage()){
                            game_field.remove_dead_unit_view((*enemy)->get_view());
                            enemy_list.removeOne(*enemy);
                            total_score += (*enemy)->get_enemy_score();
                            update_score_bar = true;
                            break; // no need further checking if the enemy is dead
                        }
                    }
                }
            }

            // enemy vs player
            if (collide((*enemy), player)) {
                static int delay = 0;
                delay += 1;
                if (delay%20 == 1){         // 1 hp deducted for each 0.2s // TODO :: rate too high?
                    update_hp_bar = true;
                    // TODO :: enemy also takes damage?
                    if(player->take_damage()) {
                        game_field.remove_dead_unit_view(player->get_view());
                    }
                }
            }
        }
    }

    // enemy_bullet vs player
    if (!enemy_bullet_list.isEmpty()) {
        for (QList<Bullet*>::iterator bullet = enemy_bullet_list.begin(); bullet != enemy_bullet_list.end(); ++bullet) {
            if (collide(player, (*bullet))) {
                delete (*bullet)->get_view();
                enemy_bullet_list.removeOne(*bullet);
                update_hp_bar = true;
                if(player->take_damage()) {
                    game_field.remove_dead_unit_view(player->get_view());
                    break; // no need further checking if the player is dead
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
