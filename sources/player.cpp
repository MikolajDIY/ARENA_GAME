#include "player.h"

Player::Player(TextureMenager& textures){
    playerSprite.setTexture(textures.getPlayerTexture());
    swordSprite.setTexture(textures.getSteelSwordTexture());
    position = sf::Vector2f(120.f, 250.f);
}
void Player::Draw(sf::RenderWindow& window){
    window.draw(playerSprite);
    window.draw(swordSprite);
}

void Player::Update(){
    playerSprite.setPosition(position);
    swordSprite.setPosition(position + sf::Vector2f(75.f, 0.f));
}
