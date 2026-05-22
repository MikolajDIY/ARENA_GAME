#include "player.h"

// -------------------------------------
//            CLASS PLAYER
// -------------------------------------

Player::Player(TextureMenager& textures) : textures(textures){
    position = sf::Vector2f(120.f, 250.f);

    unlockedSwords[SwordsTypes::Basic] = true;
    unlockedSwords[SwordsTypes::Steel] = false;
    unlockedSwords[SwordsTypes::Godness] = false;

    unlockedArmors[ArmorsTypes::Basic] = true;
    unlockedArmors[ArmorsTypes::Steel] = false;
    unlockedArmors[ArmorsTypes::Godness] = false;

    sword = SwordsTypes::Basic;
    armor = ArmorsTypes::Basic;

    setArmor(armor);
    setSword(sword);

    gold = 200; // TEST
}
// -------------------------------------
// RYSOWANIE GRACZA
// -------------------------------------
void Player::Draw(sf::RenderWindow& window){
    window.draw(playerSprite);
    window.draw(swordSprite);
}

void Player::Update(){
    playerSprite.setPosition(position);
    swordSprite.setPosition(position + sf::Vector2f(15.f, 95.f));
}

void Player::Update(float x, float y){
    position = sf::Vector2f(x,y);
    playerSprite.setPosition(position);
}
// -------------------------------------
// SKLEP I USTAWIENIA - ZARZADZANIE EKWIPUNKIEM GRACZA
// -------------------------------------
int Player::getGold(){return gold;}
// ustawienie miecza, pancerza i aktualizacja tekstur
void Player::setSword(SwordsTypes newSword){
    if(unlockedSwords[newSword] == false){return;}
    sword = newSword;
    switch(sword){
    case SwordsTypes::Basic:
        swordSprite.setTexture(textures.getBasicSwordTexture());
        break;

    case SwordsTypes::Steel:
        swordSprite.setTexture(textures.getSteelSwordTexture());
        break;

    case SwordsTypes::Godness:
        swordSprite.setTexture(textures.getGodnesSwordTexture());
        break;
    }
}
void Player::setArmor(ArmorsTypes newArmor){
    if(unlockedArmors[newArmor] == false){return;}

    armor = newArmor;
    switch(armor){
    case ArmorsTypes::Basic:
        playerSprite.setTexture(textures.getPlayerTextureBasic());
        break;

    case ArmorsTypes::Steel:
        playerSprite.setTexture(textures.getPlayerTextureSteel());
        break;

    case ArmorsTypes::Godness:
        playerSprite.setTexture(textures.getPlayerTextureGodnes());
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
