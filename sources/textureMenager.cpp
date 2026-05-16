#include "textureMenager.h"

TextureMenager::TextureMenager(){
    // Ladowanie czcionki
    if (!mainFont.loadFromFile("fonts/Cinzel_Decorative/CinzelDecorative-Bold.ttf")) {
        mainFont.loadFromFile("C:/Windows/Fonts/arial.ttf"); // Gdyby sie nie wczytalo
    }
    gameName.loadFromFile("img/intro/the-arena.png");
    studio.loadFromFile("img/intro/intro.png");

    basicSwordTexture.loadFromFile("img/s_basic.png");
    playerTextureBasic.loadFromFile("img/p_basic.png");

    steelSwordTexture.loadFromFile("img/s_steel.png");
    playerTextureSteel.loadFromFile("img/p_steel.png");

    godnesSwordTexture.loadFromFile("img/s_godnes.png");
    playerTextureGodnes.loadFromFile("img/p_godnes.png");
}
TextureMenager::~TextureMenager(){

}

sf::Font& TextureMenager::getMainFont(){return mainFont;}
sf::Texture& TextureMenager::getGameName(){return gameName;}
sf::Texture& TextureMenager::getStudio(){return studio;}

sf::Texture& TextureMenager::getPlayerTextureBasic(){return playerTextureBasic;}
sf::Texture& TextureMenager::getBasicSwordTexture(){return basicSwordTexture;}

sf::Texture& TextureMenager::getPlayerTextureSteel(){return playerTextureSteel;}
sf::Texture& TextureMenager::getSteelSwordTexture(){return steelSwordTexture;}

sf::Texture& TextureMenager::getPlayerTextureGodnes(){return playerTextureGodnes;}
sf::Texture& TextureMenager::getGodnesSwordTexture(){return godnesSwordTexture;}

sf::Texture& TextureMenager::getSkeleton(){return SkeletonTexture;}
sf::Texture& TextureMenager::getZombie(){return ZombieTexture;}
sf::Texture& TextureMenager::getMage(){return MageTexture;}
sf::Texture& TextureMenager::getBoss(){return BossTexture;}
