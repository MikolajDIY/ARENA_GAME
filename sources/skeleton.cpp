#pragma once
#include "skeleton.h"
#include "stats.h"
#include "player.h"

Skeleton::Skeleton(TextureMenager& textures) : Enemy(textures){
    enemyDraw.EnemySprite.setTexture(textures.getSkeleton());
    name = "Skeleton";
    type = EnemyTypes::Skeleton;
    enemyDraw.Name.setString(name);
    Utils::ObjectFormatter<sf::Text>::formatText(enemyDraw.Name);

    // Staty na potrzeby testu - do balansu
    stats.health = Stats::enemy.at(type).health;
    stats.damage = Stats::enemy.at(type).damage;

    gold = 10;
    points = 50;
}

void Skeleton::HpBarUpdate(){
    Enemy::HpBarUpdate();

    // IMIE oraz HP
    enemyDraw.Name.setPosition(position + sf::Vector2f(60.f, -25.f));
    enemyDraw.HpBar.setPosition(position + sf::Vector2f(60.f, -5.f));
}

void Skeleton::Attack(Player& target) {
    target.TakeDamage(this->stats.damage);
}
