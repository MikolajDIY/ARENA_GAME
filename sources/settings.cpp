#include "settings.h"
#include "button.h"
#include "theme.h"

 Settings::Settings(TextureMenager& textures, Player& player){
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(80,40);
 }

 Settings::~Settings(){
    delete btnBackToMenu;
 }

bool Settings::Update(int mouseX, int mouseY, bool isClicked){
    if (btnBackToMenu->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }
    return true;
 }

void Settings::Draw(sf::RenderWindow& window){
    btnBackToMenu->Draw(window);
 }
