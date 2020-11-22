#include "Enemy.h"

//Conversion Constructor
Enemy::Enemy(float hp, float attack, int velocity[2], int pos[2], int shooting_interval, int MAX_HP, float shooting_chance, int enemy_score):
    Unit(hp, attack, velocity, pos, shooting_interval, MAX_HP), shooting_chance(shooting_chance), enemy_score(enemy_score) {}

//Simple Accessor
Enemy::get_shooting_chance(){
    return shooting_chnace;
}
Enemy::get_enemy_score(){
    return enemy_score;
}

//idk what these are called
virtual void shoot(){}
virtual void take_damage(float raw_damage){
    if (raw_damage > hp) hp = 0;
    else hp -= raw_damage;
}