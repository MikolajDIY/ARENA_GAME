#include "item.h"
#include "utils.h"
#include "theme.h"

//---------------------------------------------
//      OBECNIE ITEM JEST TYKO DLA SKLEPU
//---------------------------------------------

Item::Item(sf::Texture& texture, sf::Font& font, sf::Vector2f pos, std::string name, int pricee){
    // Textuta Itemu
    itemSprite.setTexture(texture);
    Utils::ObjectFormatter<sf::Sprite>::centerOrigin(itemSprite);
    itemSprite.setPosition(pos);

    // Tlo
    sf::Vector2f siz(itemSprite.getLocalBounds().width + 15, itemSprite.getLocalBounds().height +15);
    background.setSize(siz);
    Utils::ObjectFormatter<sf::Shape>::centerOrigin(background);
    background.setPosition(pos);
    background.setFillColor(Theme::ButtonNormal);
    background.setOutlineThickness(3.f);
    background.setOutlineColor(Theme::ButtonOutline);

    // Text Ceny
    price = pricee;
    priceText.setFont(font);
    priceText.setString(std::to_string(price)+" G");
    Utils::ObjectFormatter<sf::Text>::formatText(priceText);
    priceText.setCharacterSize(15);
    priceText.setFillColor(Theme::Text);
    priceText.setPosition(pos.x + priceText.getLocalBounds().width/2.f - 20, pos.y + background.getLocalBounds().height/2.f +40);

    // Text Nazwy
    nameText.setFont(font);
    nameText.setString(name);
    Utils::ObjectFormatter<sf::Text>::formatText(nameText);
    nameText.setCharacterSize(15);
    nameText.setFillColor(Theme::Text);
    nameText.setPosition(pos.x + nameText.getLocalBounds().width/2.f , pos.y + background.getLocalBounds().height/2.f +20);
}

// Animacja i sprawdzenie czy klikniety
bool Item::IsClicked(Utils::Mouse& mouse, bool isBought){
    bool Hovered = background.getGlobalBounds().contains(mouse.pos);
    if(isBought){
        if(Hovered){
            background.setFillColor(Theme::Grey);
        }
        else{
            background.setFillColor(Theme::Grey);
        }
        return false;
    }

    if(Hovered){
        background.setFillColor(Theme::ButtonHover);
    }
    else{
        background.setFillColor(Theme::ButtonNormal);
    }
    return Hovered && mouse.clickedLeft;
}
// Zwykle info czy klikniety - dla SHOP
bool Item::IsClicked(Utils::Mouse& mouse){
    bool Hovered = background.getGlobalBounds().contains(mouse.pos);

    return Hovered && mouse.clickedLeft;
}

int Item::getPrice(){return price;}

// Ustawienie stanu itemu - czy jest kupiony/posiadany/wyposa¿ony
void Item::setState(const ItemState state){
    itemState = state;
}

void Item::Update(){
    switch(itemState){
        case ItemState::Blocked:
            priceText.setString(std::to_string(price)+" G");
            Utils::ObjectFormatter<sf::Text>::formatText(priceText);
            break;

        case ItemState::Aviable:
            priceText.setString("Aviable");
            Utils::ObjectFormatter<sf::Text>::formatText(priceText);
            break;

        case ItemState::Euiped:
            priceText.setString("Equiped");
            Utils::ObjectFormatter<sf::Text>::formatText(priceText);
            break;
    }
}

// Rysowanie itemu
void Item::Draw(sf::RenderWindow& window){
    Update();
    window.draw(background);
    window.draw(itemSprite);
    window.draw(priceText);
    window.draw(nameText);
}
