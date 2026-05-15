#include "player.h"

Player::Player(TextureMenager& textures) : textures(textures){
    playerSprite.setTexture(textures.getPlayerTextureBasic());
    swordSprite.setTexture(textures.getBasicSwordTexture());
    position = sf::Vector2f(120.f, 250.f);
}
void Player::Draw(sf::RenderWindow& window){
    window.draw(playerSprite);
    window.draw(swordSprite);
}

void Player::Update(){
    playerSprite.setPosition(position);
    swordSprite.setPosition(position + sf::Vector2f(15.f, 95.f));
}
