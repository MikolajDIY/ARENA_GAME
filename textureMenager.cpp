#include "textureMenager.h"

TextureMenager::TextureMenager(){
    // Ladowanie czcionki
    if (!mainFont.loadFromFile("fonts/porkybold.otf")) {
        mainFont.loadFromFile("C:/Windows/Fonts/arial.ttf"); // Gdyby sie nie wczytalo
    }

    testSword.loadFromFile("img/testSword.png");
    playerTexture.loadFromFile("img/player.png");
}
TextureMenager::~TextureMenager(){

}

sf::Font& TextureMenager::getMainFont(){return mainFont;}
sf::Texture& TextureMenager::getPlayerTexture(){return playerTexture;}
