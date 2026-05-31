#pragma once
#include "mage.h"
#include "stats.h"
#include "player.h"

Mage::Mage(TextureMenager& textures) : Enemy(textures){
    enemyDraw.EnemySprite.setTexture(textures.getMage());
    name = "Mage";
    type = EnemyTypes::Mage;
    enemyDraw.Name.setString(name);
    Utils::CenterTextOrigin(enemyDraw.Name);

    // Staty na potrzeby testu - do balansu
    stats.health = Stats::enemy.at(type).health;
    stats.damage = Stats::enemy.at(type).damage;

    gold = 50;
    points = 200;
}

void Mage::HpBarUpdate(){
    Enemy::HpBarUpdate();

    // IMIE oraz HP
    enemyDraw.Name.setPosition(position + sf::Vector2f(40.f, -25.f));
    enemyDraw.HpBar.setPosition(position + sf::Vector2f(40.f, -5.f));
}

void Mage::Attack(Player& target) {
    target.TakeDamage(this->stats.damage);
}
