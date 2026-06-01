#include "player.h"
#include "stats.h"

// -------------------------------------
//            CLASS PLAYER
// -------------------------------------

Player::Player(TextureMenager& textures) : textures(textures){
    position = sf::Vector2f(100.f, 250.f);

// ODBLOKOWANE ITMEY - Do ubrania w ustawieniach
//  Wczytanie danych gracza z pliku, bedzie oznaczaolo wyczyszczenie map 'unlockedSwords'
//  oraz 'unlockesArmors' oraz wypelenie ich wartosciami z pliku.
    // Miecze
    unlockedSwords[SwordsTypes::Basic] = true;
    unlockedSwords[SwordsTypes::Steel] = false;
    unlockedSwords[SwordsTypes::Godness] = false;
    // Zbroje
    unlockedArmors[ArmorsTypes::Basic] = true;
    unlockedArmors[ArmorsTypes::Steel] = false;
    unlockedArmors[ArmorsTypes::Godness] = false;

    // Wczytanie domyslnego ubioru na potrzeby testu - DOCELOWO MA BYC TU WYWOLANIE METODY ODCZYTUJACEJ EKWIPUNEK Z PLIKU
    // I UBRANIE OSTATNIEGO ZAPISANEGO SETU.
    sword = SwordsTypes::Basic;
    armor = ArmorsTypes::Basic;
    name = "Victoria";

// Ustawia tekstury i statystyki
    Utils::CenterSpriteOrigin(playerDraw.PlayerSprite);
    Utils::CenterSpriteOrigin(playerDraw.SwordSprite);
    setArmor(armor);
    setSword(sword);
    // Ustawienie Hp Bar
    playerDraw.HpBar.setCharacterSize(15);
    playerDraw.HpBar.setFont(textures.getMainFont());
    Utils::CenterTextOrigin(playerDraw.HpBar);
    // Ustawienie Name Bar
    playerDraw.Name.setCharacterSize(15);
    playerDraw.Name.setFont(textures.getMainFont());
    Utils::CenterTextOrigin(playerDraw.Name);
    playerDraw.Name.setString(name);

    gold = 200; // TEST
}
// -------------------------------------
// RYSOWANIE GRACZA
// -------------------------------------
void Player::Draw(sf::RenderWindow& window){
    Update();
    window.draw(playerDraw.PlayerSprite);
    window.draw(playerDraw.SwordSprite);
    window.draw(playerDraw.HpBar);
    window.draw(playerDraw.Name);
}

void Player::Update(){ // Wywolac po otrzymaniu ataku wykonaniu ataku, jezeli bedzi jakas 'mana' tu zaktualizowac
    playerDraw.PlayerSprite.setPosition(position);
    playerDraw.SwordSprite.setPosition(position + sf::Vector2f(15.f, 95.f));

    playerDraw.Name.setPosition(position + sf::Vector2f(10.f, -35.f));
    HpBarUpdate();
}

void Player::Update(float x, float y){ // Wywolac przy zamianie pozycji gracza - jezeli bedzie trzeba
    position = sf::Vector2f(x,y);
    Update();
}
// POKAZANIE HP
void Player::HpBarUpdate(){
    playerDraw.HpBar.setString(std::to_string(stats.health) + " Hp");
    if(stats.health <= 0.2*Stats::armor.at(armor).value){
        playerDraw.HpBar.setFillColor(sf::Color::Red);
    }
    else{
        playerDraw.HpBar.setFillColor(sf::Color::Green);
    }
    playerDraw.HpBar.setPosition(position + sf::Vector2f(30.f, -20.f));
}
// -------------------------------------
// SKLEP I USTAWIENIA - ZARZADZANIE EKWIPUNKIEM GRACZA
// -------------------------------------
int Player::getGold(){return gold;}
// ustawienie miecza, pancerza i aktualizacja tekstur
void Player::setSword(SwordsTypes newSword){
    if(unlockedSwords[newSword] == false){return;}
    sword = newSword;

    // Zmiana statystyk gracza
    stats.demage = Stats::sword.at(sword).value;

    // Podmiana tekstur miecza
    switch(sword){
    case SwordsTypes::Basic:
        playerDraw.SwordSprite.setTexture(textures.getBasicSwordTexture());
        break;

    case SwordsTypes::Steel:
        playerDraw.SwordSprite.setTexture(textures.getSteelSwordTexture());
        break;

    case SwordsTypes::Godness:
        playerDraw.SwordSprite.setTexture(textures.getGodnesSwordTexture());
        break;
    }
}
void Player::setArmor(ArmorsTypes newArmor){
    if(unlockedArmors[newArmor] == false){return;}
    armor = newArmor;

    // Zmiana statystyk gracza
    stats.health = Stats::armor.at(armor).value;

    // Zmiana statystyk gracza
    switch(armor){
    case ArmorsTypes::Basic:
        playerDraw.PlayerSprite.setTexture(textures.getPlayerTextureBasic());
        break;

    case ArmorsTypes::Steel:
        playerDraw.PlayerSprite.setTexture(textures.getPlayerTextureSteel());
        break;

    case ArmorsTypes::Godness:
        playerDraw.PlayerSprite.setTexture(textures.getPlayerTextureGodnes());
        break;
    }
}
// Czy ma pancerz
bool Player::hasSword(SwordsTypes sword) const{
    return unlockedSwords.at(sword);
}
bool Player::hasArmor(ArmorsTypes armor) const{
    return unlockedArmors.at(armor);
}
// Odblokowanie itemu
void Player::unlockSword(SwordsTypes sword){
    unlockedSwords[sword] = true;
}
void Player::unlockArmor(ArmorsTypes armor){
    unlockedArmors[armor] = true;
}
// Zakup itemu
bool Player::buySword(SwordsTypes sword, int price){
    if(hasSword(sword)){
        return false;
    }
    else if(gold<price){
        return false;
    }
    else{
        gold -= price;
        unlockSword(sword);
        setSword(sword);
        return true;
    }
}

bool Player::buyArmor(ArmorsTypes armor, int price){
    if(hasArmor(armor)){
        return false;
    }
    else if(gold<price){
        return false;
    }
    else{
        gold -= price;
        unlockArmor(armor);
        setArmor(armor);
        return true;
    }
}
