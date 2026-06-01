#pragma once
#include "boss.h"
#include "stats.h"

Boss::Boss(TextureMenager& textures) : Enemy(textures){
    enemyDraw.EnemySprite.setTexture(textures.getBoss());
    name = "THE UNDYING EMPEROR";
    type = EnemyTypes::Boss;
    enemyDraw.Name.setString("The Undying");
    Utils::CenterTextOrigin(enemyDraw.Name);

    // Inicjalizacja Name2 - za dlugie na jedna linie
    enemyDraw.Name2.setString("Emperor");
    enemyDraw.Name2.setCharacterSize(15);
    enemyDraw.Name2.setFont(textures.getMainFont());
    Utils::CenterTextOrigin(enemyDraw.Name2);

    // Staty na potrzeby testu - do balansu
    stats.health = Stats::enemy.at(type).health;
    stats.damage = Stats::enemy.at(type).damage;

    gold = 1000;
    points = 5000;
}

void Boss::HpBarUpdate(){
    Enemy::HpBarUpdate();

    // IMIE oraz HP
    enemyDraw.Name.setPosition(position + sf::Vector2f(90.f, -40.f));
    enemyDraw.Name2.setPosition(position + sf::Vector2f(90.f, -20.f));
    enemyDraw.HpBar.setPosition(position + sf::Vector2f(90.f, 0.f));
}

void Boss::Draw(sf::RenderWindow& window){
    Enemy::Draw(window);
    window.draw(enemyDraw.Name2);
}
