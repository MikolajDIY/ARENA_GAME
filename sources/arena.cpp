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
    msgManager = new MessageMenager(menagers.tex);
    msgManager->add("Rozpoczeto walke na " + name, MessageType::Success, 2.5f); //przykladowa wartosc

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

    //licznik tur
    currentTurn = 1;
    maxTurns = 10; //przykladowa wartosc

    // Przykladowo dodany wrog
    //enemies.push_back(new Zombie(menagers.tex)); // Moze lepiej trzymac ich w std::map ?
    //enemies[0]->Update(320,250);

   // enemies.push_back(new Boss(menagers.tex));
    //enemies[1]->Update(520,220);

    //enemies.push_back(new Mage(menagers.tex));
    //enemies[0]->Update(320,250);

    enemies.push_back(new Skeleton(menagers.tex));
    enemies[0]->Update(320,250);
    enemies.push_back(new Skeleton(menagers.tex));
    enemies[1]->Update(520,250);
}

Arena::~Arena(){
    delete btnBackToMenu;
    delete btnAttackBasic;
    delete btnAttackReckless;
    delete btnAttackRisky;
    delete btnAttackCombo;
    delete btnHeal;
    delete msgManager;
    for(auto enemy : enemies){
        delete enemy;
    }
}

void Arena::Fight(){
    // Mechanika walki
    switch(currentState) {
        case TurnState::PlayerMove:
            break;

        case TurnState::PlayerAttack:
            selectedEnemy = nullptr;
            isPlayerSelected = false;
            currentState = TurnState::EnemiesTurn;
            break;

        case TurnState::EnemiesTurn:
        {
            if (turnDelayClock.getElapsedTime().asSeconds() < 3.0f) //przykladowa wartosc opoznienia
            return;

            int hpBefore = player.getHealth();
            for (auto const& enemy : enemies) {
                if (player.getHealth() > 0)
                    enemy->Attack(player);
            }
            int totalDamageTaken = hpBefore - player.getHealth();

            if (totalDamageTaken > 0) {
            msgManager->add("You took " + std::to_string(totalDamageTaken) + " damage!", MessageType::Error, 2.0f);
            }

            currentTurn++;
            if(!CheckGameOverConditions()) {
                currentState = TurnState::PlayerMove;
            }
            break;
        }
        case TurnState::GameOver:
            break;
    }
}

// WARUNKI KONCA GRY
bool Arena::CheckGameOverConditions() {
    // Gracz straci³ ca³e HP
    if (player.getHealth() <= 0) {
        msgManager->add("DEFEAT!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("Victoria  has   fallen...", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    // Brak wrogów na arenie
    if (enemies.empty()) {
        msgManager->add("VICTORY!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("All  enemies  vanquished!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    // Skoñczy³y siê tury
    if (currentTurn > maxTurns) {
        msgManager->add("DEFEAT!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("You ran out of time! Max turns reached.", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    return false;
}

// METODY POMOCNICZE DO Arena::Update
void Arena::HandleTargetSelection(const sf::Vector2f& mouseCoord) {
    // Klikniêcie w samego gracza - leczenie
    if (player.getSprite().getGlobalBounds().contains(mouseCoord)) {
        isPlayerSelected = true;
        selectedEnemy = nullptr;
    }
    // Klikniêcie w przeciwnika - atak
    else {
        for (Enemy* enemy : enemies) {
            if (enemy->getSprite().getGlobalBounds().contains(mouseCoord)) {
                selectedEnemy = enemy;
                isPlayerSelected = false;
                break;
            }
        }
    }
}

void Arena::ExecuteAttack(AttackType attackType) {
    if (!selectedEnemy) return;

    int hpBefore = selectedEnemy->getHealth();
    player.Hit(*selectedEnemy, attackType);
    int damageDealt = hpBefore - selectedEnemy->getHealth();

    msgManager->add("Dealt " + std::to_string(damageDealt) + " damage to enemy!", MessageType::Success, 2.0f);

    if (selectedEnemy->isDead()) {
        HandleEnemyDefeat();
    } else {
        selectedEnemy = nullptr;
        if (!CheckGameOverConditions()) {
            currentState = TurnState::EnemiesTurn;
            turnDelayClock.restart();
        }
    }
}

void Arena::HandleEnemyDefeat() {
    msgManager->add("Enemy defeated!", MessageType::Success, 3.0f);

    enemies.erase(std::remove(enemies.begin(), enemies.end(), selectedEnemy), enemies.end());
    delete selectedEnemy;
    selectedEnemy = nullptr;

    if(!CheckGameOverConditions()) {
        currentState = TurnState::EnemiesTurn;
        turnDelayClock.restart();
    }
}

void Arena::HandlePlayerAttacks(Utils::Mouse& Mouse) {
    if (btnAttackBasic->IsClicked(Mouse))    { ExecuteAttack(AttackType::Basic); }
    else if (btnAttackReckless->IsClicked(Mouse)) { ExecuteAttack(AttackType::Reckless); }
    else if (btnAttackRisky->IsClicked(Mouse))    { ExecuteAttack(AttackType::Risky); }
    else if (btnAttackCombo->IsClicked(Mouse))    { ExecuteAttack(AttackType::Combo); }
}

// -------------------------------------
// RYSOWANIE ARENY
// -------------------------------------
bool Arena::Update(Utils::Mouse& Mouse) {
    msgManager->update();

    if (btnBackToMenu->IsClicked(Mouse)) {
        return false;
    }
    if (currentState == TurnState::GameOver) {
        return true;
    }

    if(currentState == TurnState::PlayerMove) {
    if(Mouse.clickedLeft) {
        HandleTargetSelection(Mouse.pos);
    }
        if(selectedEnemy != nullptr) {
                HandlePlayerAttacks(Mouse);
        }
        if (isPlayerSelected && btnHeal->IsClicked(Mouse)) {
            int hpBefore = player.getHealth();
            player.Heal(10);
            int healedAmount = player.getHealth() - hpBefore;
            msgManager->add("Healed for " + std::to_string(healedAmount) + " HP!", MessageType::Success, 2.0f);

            isPlayerSelected = false;
            currentState = TurnState::EnemiesTurn;
            turnDelayClock.restart();
        }
    }
    Fight(); // Logika walki
    return true;
}

void Arena::Draw(sf::RenderWindow& window){
    // Rysowanie Areny
    window.draw(arenaBackGround);
    // Rysowanie Przeciwnikow
    for(auto const& enemy : enemies){  // Przy zmianie przechowywania na std::map ZMIENIC
        enemy->Update();
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
    msgManager->Draw(window);
}



