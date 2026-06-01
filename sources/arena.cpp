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

    //Przyciski ataku
    float btnWidth = 160.f, btnHeight = 45.f, Y_Position = 520.f;

    btnAttackBasic    = new Button("Basic",    {58.f, Y_Position},  menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnAttackReckless = new Button("Reckless", {233.f, Y_Position}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnAttackRisky    = new Button("Risky",    {408.f, Y_Position}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnAttackCombo    = new Button("Combo",    {583.f, Y_Position}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);

    btnAttackBasic->ChangeSize(btnWidth, btnHeight);
    btnAttackReckless->ChangeSize(btnWidth, btnHeight);
    btnAttackRisky->ChangeSize(btnWidth, btnHeight);
    btnAttackCombo->ChangeSize(btnWidth, btnHeight);

    btnHeal = new Button("Heal", {320.f, Y_Position}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnHeal->ChangeSize(btnWidth, btnHeight);

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
    delete btnAttackBasic;
    delete btnAttackReckless;
    delete btnAttackRisky;
    delete btnAttackCombo;
    delete btnHeal;
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

    sf::Vector2f mouseCoord = Mouse.pos;
    if(Mouse.clickedLeft) {
        // Klikniêcie w samego gracza - leczenie
        if (player.getSprite().getGlobalBounds().contains(mouseCoord)) {
        isPlayerSelected = true;
        selectedEnemy = nullptr;
        }
        // Klikniêcie w przeciwnika - atak
        else {
            for(Enemy* enemy : enemies) {
                if(enemy->getSprite().getGlobalBounds().contains(mouseCoord)) {
                    selectedEnemy = enemy;
                    isPlayerSelected = false;
                    break;
                }
            }
        }
    }
        if(selectedEnemy != nullptr) {
            if(btnAttackBasic->IsClicked(Mouse)) {
                player.Hit(*selectedEnemy, AttackType::Basic);
                selectedEnemy = nullptr;
                // currentState = TurnState::EnemiesTurn;
            }
            else if(btnAttackReckless->IsClicked(Mouse)) {
                player.Hit(*selectedEnemy, AttackType::Reckless);
                selectedEnemy = nullptr;
                // currentState = TurnState::EnemiesTurn;
            }
            else if(btnAttackRisky->IsClicked(Mouse)) {
                player.Hit(*selectedEnemy, AttackType::Risky);
                selectedEnemy = nullptr;
                // currentState = TurnState::EnemiesTurn;
            }
            else if(btnAttackCombo->IsClicked(Mouse)) {
                player.Hit(*selectedEnemy, AttackType::Combo);
                selectedEnemy = nullptr;
                // currentState = TurnState::EnemiesTurn;
            }
        }

        if(isPlayerSelected && btnHeal->IsClicked(Mouse)) {
            player.Heal(10); //przykladowa wartosc
            isPlayerSelected = false;
            // currentState = TurnState::EnemiesTurn;
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

    //Rysowanie przyciskow atakow
    if (selectedEnemy != nullptr) {
        btnAttackBasic->Draw(window);
        btnAttackReckless->Draw(window);
        btnAttackRisky->Draw(window);
        btnAttackCombo->Draw(window);
    }

    // Rysowanie przycisku leczenia
    if (isPlayerSelected) {
        btnHeal->Draw(window);
    }
}



