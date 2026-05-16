#include "shop.h"
#include "game.h"
#include "theme.h"

 Shop::Shop(TextureMenager& textures, Player& player){
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(80,40);
 }

 Shop::~Shop(){
    delete btnBackToMenu;
 }

bool Shop::Update(int mouseX, int mouseY, bool isClicked){
    if (btnBackToMenu->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }
    return true;
 }

void Shop::Draw(sf::RenderWindow& window){
    btnBackToMenu->Draw(window);
 }
