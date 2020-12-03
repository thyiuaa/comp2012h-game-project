#include "Enemy.h"
#include <QDebug>

//Constructor
Enemy::Enemy(int hp, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float shooting_chance, int enemy_score):
    Unit(hp, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height), shooting_chance(shooting_chance), enemy_score(enemy_score) {
    icon_path = "://images/enemy_icon_temp.png";
}

//Destructor
Enemy::~Enemy(){
}

//Simple Accessor
float Enemy::get_shooting_chance(){
    return shooting_chance;
}

int Enemy::get_enemy_score(){
    return enemy_score;
}

//idk what these are called
void Enemy::update_pos(){
    move_down();
    move_left();
    if (pos_x <= 0 || pos_x >= 570) velocity_x *= -1;
}
Bullet* Enemy::shoot(){

    int bullet_width = QPixmap("://images/enemy_fire.png").width();
    int bullet_height = QPixmap("://images/enemy_fire.png").height();
    int bullet_pos_x = pos_x + (width-bullet_width)/2;
    int bullet_pos_y = pos_y + height;
    int bullet_velocity = -(velocity_y + 1); //speed but not velocity

    if (shooting_cooldown == 0){
        shooting_cooldown = shooting_interval;
        if (shooting_chance > 1){
            Bullet* bullet = new Bullet(bullet_width, bullet_height, bullet_pos_x, bullet_pos_y, bullet_velocity);
            shooting_chance -= 1;
            return bullet;
        }
        shooting_chance = (shooting_chance+0.2)*1.5;
    }
    return nullptr;
}

//void Enemy::take_damage(float raw_damage){
//    if (raw_damage > hp) hp = 0;
//    else hp -= raw_damage;
//}
