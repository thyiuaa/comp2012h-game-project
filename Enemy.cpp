#include "Enemy.h"

//Conversion Constructor
Enemy::Enemy(float hp, float attack, int velocity_x, int velocity_y, int pos_x, int pos_y, int shooting_interval, int MAX_HP, int width, int height, float shooting_chance, int enemy_score):
    Unit(hp, attack, velocity_x, velocity_y, pos_x, pos_y, shooting_interval, MAX_HP, width, height), shooting_chance(shooting_chance), enemy_score(enemy_score) {}

//Simple Accessor
float Enemy::get_shooting_chance(){
    return shooting_chance;
}

int Enemy::get_enemy_score(){
    return enemy_score;
}

//idk what these are called
Bullet* Enemy::shoot(){}

void Enemy::take_damage(float raw_damage){
    if (raw_damage > hp) hp = 0;
    else hp -= raw_damage;
}
