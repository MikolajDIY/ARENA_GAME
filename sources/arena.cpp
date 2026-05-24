#include "arena.h"
#include "textureMenager.h"
#include "player.h"
#include "theme.h"
#include "skeleton.h"
#include "zombie.h"
#include "mage.h"
#include "boss.h"

Arena::Arena(std::string arenaName, Utils::Menagers& menagers, Player& mainPlayer) : menagers(menagers), player(mainPlayer){
    name = arenaName;
    currentState = TurnState::PlayerMove;
    btnBackToMenu = new Button("MENU", {10,10}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(90,40);
    arenaBackGround.setTexture(menagers.tex.getArenaBackGround());

    // Przykladowo dodany wrog
    enemies.push_back(new Zombie(menagers.tex)); // Moze lepiej trzymac ich w std::map ?
    enemies[0]->Update(320,250);

    enemies.push_back(new Boss(menagers.tex));
    enemies[1]->Update(520,220);

    //enemies.push_back(new Mage(menagers.tex));
    //enemies[0]->Update(320,250);

    //enemies.push_back(new Skeleton(menagers.tex));
    //enemies[1]->Update(320,250);
}

Arena::~Arena(){
    delete btnBackToMenu;
    for(auto enemy : enemies){
        delete enemy;
    }
}

void Arena::Fight(){
    // Mechanika walki
}

// -------------------------------------
// RYSOWANIE ARENY
// -------------------------------------
bool Arena::Update(Utils::Mouse& Mouse) {
    if (btnBackToMenu->IsClicked(Mouse)) {
        return false;
    }

    Fight(); // Logika walki
    return true;
}

void Arena::Draw(sf::RenderWindow& window){
    // Rysowanie Areny
    window.draw(arenaBackGround);
    // Rysowanie Przeciwnikow
    for(auto const& enemy : enemies){  // Przy zmianie przechowywania na std::map ZMIENIC
        enemy->Draw(window);
    }
    // Rysowania Gracza
    player.Update();
    player.Draw(window);

    //Rysowanie Przyciskow
    btnBackToMenu->Draw(window);
}



