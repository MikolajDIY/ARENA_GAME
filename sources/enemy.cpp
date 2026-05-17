#include "enemy.h"
// -------------------------------------
//            CLASS ENEMY
// -------------------------------------

Enemy::Enemy(TextureMenager& textures) : textures(textures){
    position = sf::Vector2f(120.f, 250.f);
    gold =0;
    points=0;
    isDeath = false;
}
// -------------------------------------
// RYSOWANIE PRZECIWNIKA
// -------------------------------------
void Enemy::Draw(sf::RenderWindow& window){
    window.draw(enemySprite);
}

void Enemy::Update(){
    enemySprite.setPosition(position);
}

void Enemy::Update(float x, float y){
    position = sf::Vector2f(x,y);
    enemySprite.setPosition(position);
}


