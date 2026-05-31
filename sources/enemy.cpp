#include "enemy.h"
#include "utils.h"
#include "stats.h"
// -------------------------------------
//            CLASS ENEMY
// -------------------------------------

Enemy::Enemy(TextureMenager& textures) : textures(textures){
    position = sf::Vector2f(120.f, 250.f);
    gold =0;
    points=0;

    Utils::CenterSpriteOrigin(enemyDraw.EnemySprite);

    enemyDraw.HpBar.setString(std::to_string(stats.health) + " Hp");
    enemyDraw.HpBar.setFont(textures.getMainFont());
    enemyDraw.HpBar.setCharacterSize(15);
    Utils::CenterTextOrigin(enemyDraw.HpBar);

    enemyDraw.Name.setFont(textures.getMainFont());
    enemyDraw.Name.setCharacterSize(15);
    Utils::CenterTextOrigin(enemyDraw.Name);

    isDeath = false;
}
// -------------------------------------
// RYSOWANIE PRZECIWNIKA
// -------------------------------------
void Enemy::Draw(sf::RenderWindow& window){
    window.draw(enemyDraw.EnemySprite);
    window.draw(enemyDraw.HpBar);
    window.draw(enemyDraw.Name);
}

void Enemy::Update(){
    enemyDraw.EnemySprite.setPosition(position);

    HpBarUpdate();
}

void Enemy::Update(float x, float y){
    position = sf::Vector2f(x,y);
    Update();
}
// POKAZANIE HP
void Enemy::HpBarUpdate(){
    enemyDraw.HpBar.setString(std::to_string(stats.health) + " Hp");
    Utils::CenterTextOrigin(enemyDraw.HpBar);
    if(stats.health <= 0.2*Stats::enemy.at(type).health){
        enemyDraw.HpBar.setFillColor(sf::Color::Red);
    }
    else{
        enemyDraw.HpBar.setFillColor(sf::Color::Green);
    }
}

void Enemy::TakeDamage(int amount) {
    stats.health -= amount;
    if (stats.health < 0)
        stats.health = 0;
}


