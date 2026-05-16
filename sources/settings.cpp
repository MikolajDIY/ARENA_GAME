#include "settings.h"
#include "button.h"
#include "theme.h"
#include "utils.h"

 Settings::Settings(TextureMenager& textures, Player& player){
    buttons["BackToMenu"] = new Button("Menu", {10,10},textures.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80,40);

    texts["Settings"] = sf::Text("Settings",textures.getMainFont(), 60);
    Utils::CenterTextOrigin(texts["Settings"]);
    texts["Settings"].setPosition(400,40);
 }

 Settings::~Settings(){
    for (auto const& pair : buttons){
        delete pair.second;
    }
    buttons.clear();
 }

bool Settings::Update(int mouseX, int mouseY, bool isClicked){
    if (buttons["BackToMenu"]->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }
    return true;
 }

void Settings::Draw(sf::RenderWindow& window){
    for(auto const& pair : buttons){
        pair.second->Draw(window);
    }
    for(auto const& pair : texts){
        window.draw(pair.second);
    }

 }
