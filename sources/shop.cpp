#include "shop.h"
#include "game.h"
#include "theme.h"
#include "utils.h"

Shop::Shop(TextureMenager& textures, Player& player, Utils::Mouse& mouse) : mouse(mouse), player(player), textures(textures){
    BackGround.setTexture(textures.getShopBackGround());
    shopState = ShopState::Armors;

    createButtons();
    createTexts();
 }

Shop::~Shop(){
    buttons.clear();
    texts.clear();
 }
void Shop::createTexts(){
    texts["Shop"] = sf::Text("Shop",textures.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Shop"]);
    texts["Shop"].setPosition(400,40);

    switch(shopState){
    case ShopState::Armors:

        break;

    case ShopState::Swords:

        break;
    }
}

void Shop::createButtons(){
    buttons["BackToMenu"] = std::make_unique<Button>("Menu", sf::Vector2f(10, 10), textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80, 40);

    buttons["Armors"] = std::make_unique<Button>("Armors", textures.getMainFont(), sf::Vector2f(50, 200), sf::Vector2f(120, 50));
    buttons["Swords"] = std::make_unique<Button>("Swords", textures.getMainFont(), sf::Vector2f(50, 300), sf::Vector2f(120, 50));

    switch(shopState){
    case ShopState::Armors:

        break;

    case ShopState::Swords:

        break;

    }
}

void Shop::changeMenu(ShopState state){
    if(shopState == state){return;}
    shopState = state;
    buttons.clear();
    texts.clear();

    createButtons();
    createTexts();
}

void Shop::buttonsClicked(){
    std::string clicked ="";
    for(auto const& button : buttons){
        if(button.second->IsClicked(mouse)){
            clicked = button.first;
        }
    }
    if(clicked == ""){return;}
    if(clicked == "Armors"){
        changeMenu(ShopState::Armors);
    }
    else if(clicked == "Swords"){
        changeMenu(ShopState::Swords);
    }
}
// -------------------------------------
// RYSOWANIE SKLEPU
// -------------------------------------
bool Shop::Update(Utils::Mouse& m){
    if (buttons.find("BackToMenu") != buttons.end() && buttons["BackToMenu"]->IsClicked(m)) {
        return false;
    }
    mouse = m;

    buttonsClicked();
    return true;
 }

void Shop::Draw(sf::RenderWindow& window){
    window.draw(BackGround);


    for(auto const& button : buttons){
        button.second->Draw(window);
    }
    for(auto const& button : texts){
        window.draw(button.second);
    }
 }
