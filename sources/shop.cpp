#include "shop.h"
#include "game.h"
#include "theme.h"
#include "utils.h"

Shop::Shop(TextureMenager& textures, Player& player) : player(player){
    BackGround.setTexture(textures.getShopBackGround());
    buttons["BackToMenu"] = new Button("Menu", {10,10},textures.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80,40);

    texts["Shop"] = sf::Text("Shop",textures.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Shop"]);
    texts["Shop"].setPosition(400,40);

 }

Shop::~Shop(){
    for (auto const& button : buttons){
        delete button.second;
    }
    buttons.clear();
 }

// -------------------------------------
// RYSOWANIE SKLEPU
// -------------------------------------
bool Shop::Update(Utils::Mouse& mouse){
    if (buttons["BackToMenu"]->IsClicked(mouse)) {
        return false;
    }
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
