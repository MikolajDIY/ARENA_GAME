#include "player.h"

Player::Player(TextureMenager& textures){
    playerSprite.setTexture(textures.getPlayerTexture());

}
void Player::Draw(sf::RenderWindow& window){
    window.draw(playerSprite);
}
