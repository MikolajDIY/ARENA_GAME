#include "arena.h"
#include "textureMenager.h"
#include "player.h"
#include "theme.h"
#include "skeleton.h"
#include "zombie.h"
#include "mage.h"
#include "boss.h"
#include "stats.h"

Arena::Arena(std::string arenaName, Utils::Menagers& menagers, Player& mainPlayer) : menagers(menagers), player(mainPlayer), currentWave(1) {
    name = arenaName;
    currentState = TurnState::PlayerMove;
    msgManager = new MessageMenager(menagers.tex);

    msgManager->add("The battle has begun", MessageType::GameIfno, 3.0f, Theme::Text, Theme::CenterOfScreen, 60);
    introClock.restart();

    maxWaves = static_cast<int>(5 * Stats::difMultipliers.at(Stats::difficulty)); //przykladowa wartosc (dla 5 - max 7)
    if (maxWaves < 1) maxWaves = 1;

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

    SpawnEnemies();
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
//GENEROWANIE PRZECIWNIKOW
void Arena::SpawnEnemies() {
    if (msgManager != nullptr && currentWave > 1)
        msgManager->add("Wave " + std::to_string(currentWave) + " starts!", MessageType::Success, 2.5f);
    static std::mt19937 gen(static_cast<unsigned long>(std::time(nullptr)));

    int minEnemies = 1;
    int maxEnemies = 3;
    std::vector<EnemyTypes> availableTypes;

    Difficulties diff = Stats::difficulty;

    if (diff == Difficulties::easy) {
        minEnemies = 1;
        maxEnemies = 2;
        availableTypes = { EnemyTypes::Skeleton, EnemyTypes::Zombie };
    }
    else if (diff == Difficulties::medium) {
        minEnemies = 2;
        maxEnemies = 3;
        availableTypes = { EnemyTypes::Skeleton, EnemyTypes::Zombie, EnemyTypes::Mage };
    }
    else if (diff == Difficulties::hard) {
        minEnemies = 3;
        maxEnemies = 4;
        availableTypes = { EnemyTypes::Skeleton, EnemyTypes::Zombie, EnemyTypes::Mage, EnemyTypes::Boss };
    }

    int waveBonus = (currentWave - 1) / 2; //mnoznik fali (nie wiem czy zostawic)
    minEnemies += waveBonus;
    maxEnemies += waveBonus;
    if (maxEnemies > 4) maxEnemies = 4;
    if (minEnemies > maxEnemies) minEnemies = maxEnemies;

    std::uniform_int_distribution<int> countDist(minEnemies, maxEnemies);
    int enemiesToSpawn = countDist(gen);

    std::uniform_int_distribution<int> typeDist(0, availableTypes.size() - 1);
    bool bossAlreadySpawned = false;

    for (int i = 0; i < enemiesToSpawn; i++) {
        int randomIndex = typeDist(gen);
        EnemyTypes chosenType = availableTypes[randomIndex];

        if (chosenType == EnemyTypes::Boss && bossAlreadySpawned)
            chosenType = EnemyTypes::Mage;
        Enemy* newEnemy = nullptr;

        switch (chosenType) {
            case EnemyTypes::Skeleton:
                newEnemy = new Skeleton(menagers.tex);
                break;
            case EnemyTypes::Zombie:
                newEnemy = new Zombie(menagers.tex);
                break;
            case EnemyTypes::Mage:
                newEnemy = new Mage(menagers.tex);
                break;
            case EnemyTypes::Boss:
                newEnemy = new Boss(menagers.tex);
                bossAlreadySpawned = true;
                break;
        }

        if (newEnemy != nullptr) {
            newEnemy->ScaleStats(Stats::difMultipliers.at(Stats::difficulty));
            enemies.push_back(newEnemy);
        }
    }
    //zmodyfikowac pozycje
    float startX = 320.f, spacingX = 130.f;

    for (size_t i = 0; i < enemies.size(); i++) {
        float currentX = startX + (i * spacingX);
        float currentY = 250.f;
        if (i % 2 == 0)
            currentY -= 20.f;
        else {
            currentY += 25.f;
        }
        if (enemies[i]->getSprite().getGlobalBounds().height > 100.f) {
            currentY = 220.f;
        }
        enemies[i]->Update(currentX, currentY);
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
    // Gracz stracil cale HP
    if (player.getHealth() <= 0) {
        msgManager->add("DEFEAT!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("Victoria  has   fallen...", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    // Brak wrogow na arenie
    if (enemies.empty()) {
        msgManager->add("VICTORY!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("All  enemies  vanquished!", MessageType::GameIfno, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    return false;
}

// METODY POMOCNICZE DO Arena::Update
void Arena::HandleTargetSelection(const sf::Vector2f& mouseCoord) {
    // Klikniecie w samego gracza - leczenie
    if (player.getSprite().getGlobalBounds().contains(mouseCoord)) {
        isPlayerSelected = true;
        selectedEnemy = nullptr;
    }
    // Klikniecie w przeciwnika - atak
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
    if (CheckGameOverConditions()) {
        return;
    }
    if (enemies.empty()) {
        currentWave++;
        SpawnEnemies();
        currentState = TurnState::PlayerMove;
    } else {
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
    if (introClock.getElapsedTime().asSeconds() < 3.0f) {
        Mouse.clickedLeft = false;
        return true;
    }
    if (!introFinished) {
        introFinished = true;
        msgManager->add("Wave " + std::to_string(currentWave) + " starts!", MessageType::Success, 2.5f);
    }
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



