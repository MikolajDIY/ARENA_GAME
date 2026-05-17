#include "textureMenager.h"

// -------------------------------------
//              CLASS TEXTUREMENAGER
// -------------------------------------

TextureMenager::TextureMenager(){
    // Ladowanie czcionki
    if (!mainFont.loadFromFile("fonts/Cinzel_Decorative/CinzelDecorative-Bold.ttf")) {
        mainFont.loadFromFile("C:/Windows/Fonts/arial.ttf"); // Gdyby sie nie wczytalo
    }
    // WCZYTANIE TLA
    menuBackGround.loadFromFile("img/backgrounds/menu.png");
    arenaBackGround.loadFromFile("img/backgrounds/arena.png");
    gameName.loadFromFile("img/intro/the-arena.png");
    studio.loadFromFile("img/intro/intro.png");
    settingsBackGround.loadFromFile("img/backgrounds/settings.png");
    shopBackGround.loadFromFile("img/backgrounds/shop.png");

    // WCZYTANIE MIECZY
    basicSwordTexture.loadFromFile("img/s_basic.png");
    steelSwordTexture.loadFromFile("img/s_steel.png");
    godnesSwordTexture.loadFromFile("img/s_godnes.png");

    // WCZYTANIE ZBROJI
    playerTextureBasic.loadFromFile("img/p_basic.png");
    playerTextureSteel.loadFromFile("img/p_steel.png");
    playerTextureGodnes.loadFromFile("img/p_godnes.png");

    // WCZYTANIE WROGOW
    MageTexture.loadFromFile("img/mag.png");
    SkeletonTexture.loadFromFile("img/skeleton.png");
    ZombieTexture.loadFromFile("img/zombie.png");
    BossTexture.loadFromFile("img/boss.png");
}
TextureMenager::~TextureMenager(){

}
// GETERY TLA
sf::Font& TextureMenager::getMainFont(){return mainFont;}
sf::Texture& TextureMenager::getGameName(){return gameName;}
sf::Texture& TextureMenager::getStudio(){return studio;}
sf::Texture& TextureMenager::getMenuBackGround(){return menuBackGround;}
sf::Texture& TextureMenager::getArenaBackGround(){return arenaBackGround;}
sf::Texture& TextureMenager::getSettingsBackGround(){return settingsBackGround;}
sf::Texture& TextureMenager::getShopBackGround(){return shopBackGround;}

// GETERY MIECZY
sf::Texture& TextureMenager::getBasicSwordTexture(){return basicSwordTexture;}
sf::Texture& TextureMenager::getSteelSwordTexture(){return steelSwordTexture;}
sf::Texture& TextureMenager::getGodnesSwordTexture(){return godnesSwordTexture;}

// GETERY ZBROJI
sf::Texture& TextureMenager::getPlayerTextureBasic(){return playerTextureBasic;}
sf::Texture& TextureMenager::getPlayerTextureSteel(){return playerTextureSteel;}
sf::Texture& TextureMenager::getPlayerTextureGodnes(){return playerTextureGodnes;}

// GETERY TEXTUR WROGA
sf::Texture& TextureMenager::getSkeleton(){return SkeletonTexture;}
sf::Texture& TextureMenager::getZombie(){return ZombieTexture;}
sf::Texture& TextureMenager::getMage(){return MageTexture;}
sf::Texture& TextureMenager::getBoss(){return BossTexture;}
