#include "item.h"
#include "utils.h"
#include "theme.h"

//---------------------------------------------
//      OBECNIE ITEM JEST TYKO DLA SKLEPU
//---------------------------------------------

Item::Item(sf::Texture& texture, sf::Font& font, sf::Vector2f pos, std::string name, float price){
    // Textuta Itemu
    itemSprite.setTexture(texture);
    Utils::CenterSpriteOrigin(itemSprite);
    itemSprite.setPosition(pos);

    // Tlo
    sf::Vector2f siz(itemSprite.getLocalBounds().width + 15, itemSprite.getLocalBounds().height +15);
    background.setSize(siz);
    Utils::CenterRectangleOrigin(background);
    background.setPosition(pos);
    background.setFillColor(Theme::ButtonNormal);
    background.setOutlineThickness(3.f);
    background.setOutlineColor(Theme::ButtonOutline);

    // Text Ceny
    price = price;
    priceText.setFont(font);
    priceText.setString(std::to_string(price)+" G");
    Utils::CenterTextOrigin(priceText);
    priceText.setCharacterSize(15);
    priceText.setFillColor(Theme::Text);
    priceText.setPosition(pos.x + priceText.getLocalBounds().width/2.f, pos.y + background.getLocalBounds().height/2.f + 50);

    // Text Nazwy
    nameText.setFont(font);
    nameText.setString(name);
    Utils::CenterTextOrigin(nameText);
    nameText.setCharacterSize(15);
    nameText.setFillColor(Theme::Text);
    nameText.setPosition(pos.x + nameText.getLocalBounds().width/2.f, pos.y + background.getLocalBounds().height/2.f +20);
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

float Item::getPrice(){return price;}

// Rysowanie itemu
void Item::Draw(sf::RenderWindow& window){
    window.draw(background);
    window.draw(itemSprite);
    window.draw(priceText);
    window.draw(nameText);
}
