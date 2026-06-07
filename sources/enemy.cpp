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

    Utils::ObjectFormatter<sf::Sprite>::centerOrigin(enemyDraw.EnemySprite);

    enemyDraw.HpBar.setString(std::to_string(stats.health) + " Hp");
    enemyDraw.HpBar.setFont(textures.getMainFont());
    enemyDraw.HpBar.setCharacterSize(15);
    Utils::ObjectFormatter<sf::Text>::formatText(enemyDraw.HpBar);

    enemyDraw.Name.setFont(textures.getMainFont());
    enemyDraw.Name.setCharacterSize(15);
    Utils::ObjectFormatter<sf::Text>::formatText(enemyDraw.Name);

    isDeath = false;
}
// Zmiana statstyk przeciwnikow
Enemy& Enemy::operator*=(float multiplier) {
    stats.health = static_cast<int>(stats.health * multiplier);
    stats.damage = static_cast<int>(stats.damage * multiplier);

    points = std::max(1, static_cast<int>(stats.health * 1.25f));
    gold   = std::max(1, static_cast<int>(stats.health * 0.75f));

    HpBarUpdate();
    return *this;
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
    Utils::ObjectFormatter<sf::Text>::formatText(enemyDraw.HpBar);
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


