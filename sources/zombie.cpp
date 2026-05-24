#pragma once
#include "zombie.h"
#include "stats.h"

Zombie::Zombie(TextureMenager& textures) : Enemy(textures){
    enemyDraw.EnemySprite.setTexture(textures.getZombie());
    name = "Zombie";
    type = EnemyTypes::Zombie;
    enemyDraw.Name.setString(name);
    Utils::CenterTextOrigin(enemyDraw.Name);

    // Staty na potrzeby testu - do balansu
    stats.health = Stats::enemy.at(type).health;
    stats.damage = Stats::enemy.at(type).damage;

    gold = 20;
    points = 100;
}

void Zombie::HpBarUpdate(){
    Enemy::HpBarUpdate();

    // IMIE oraz HP
    enemyDraw.Name.setPosition(position + sf::Vector2f(80.f, -25.f));
    enemyDraw.HpBar.setPosition(position + sf::Vector2f(80.f, -5.f));
}
