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

    msgManager->add("The battle has begun", MessageType::GameInfo, 2.5f, Theme::Text, Theme::CenterOfScreen, 60);
    introClock.restart();

    maxWaves = static_cast<int>(5 * Stats::difMultipliers.at(Stats::difficulty));
    if (maxWaves < 1) maxWaves = 1;

    btnBackToMenu = new Button("MENU", {10,10}, menagers.tex.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(90,40);
    arenaBackGround.setTexture(menagers.tex.getArenaBackGround());

    // Prygotowanie gracza
    player.setHp(Stats::armor.at(player.getArmor()).value);

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
        msgManager->add("Wave " + std::to_string(currentWave) + " starts!", MessageType::GameInfo, 2.5f, Theme::Text, Theme::CenterOfScreen, 60);
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

    int waveBonus = (currentWave - 1) / 2;
    minEnemies += waveBonus;
    maxEnemies += waveBonus;
    if (maxEnemies > 4) maxEnemies = 4;
    if (minEnemies > maxEnemies) minEnemies = maxEnemies;

    int enemiesToSpawn = Utils::getRandomInt(minEnemies, maxEnemies);
    bool bossAlreadySpawned = false;

    for (int i = 0; i < enemiesToSpawn; i++) {
        int randomIndex = Utils::getRandomInt(0, availableTypes.size() - 1);
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
            *newEnemy *= Stats::difMultipliers.at(Stats::difficulty);
            enemies.push_back(newEnemy);
        }
    }
    float startX = 270.f, baseFloorY = 260.f, spacingX = 120.f, rightBoundary = arenaBackGround.getTexture()->getSize().x;

    for (int i = 0; i < enemies.size(); ++i) {
        float posX = startX + (i * spacingX);
        float posY = (i % 2 == 0) ? (baseFloorY - 20.f) : (baseFloorY + 20.f);
        enemies[i]->Update(posX, posY);
    }
    bool moved = true;
    int maxIterations = 5;
    while (moved && maxIterations > 0) {
        moved = false;
        for (int i = 0; i < enemies.size(); ++i) {
                sf::FloatRect bounds = enemies[i]->getSprite().getGlobalBounds();
            if (bounds.left + bounds.width > rightBoundary) {
                enemies[i]->Update(rightBoundary - bounds.width, bounds.top);
            }
            for (int j = i + 1; j < enemies.size(); ++j) {
                sf::FloatRect rect1 = enemies[i]->getSprite().getGlobalBounds();
                sf::FloatRect rect2 = enemies[j]->getSprite().getGlobalBounds();

                if (rect1.intersects(rect2)) {
                    float overlap = (rect1.left + rect1.width) - rect2.left;
                    float pushAmount = overlap / 2.f + 5.f;
                    enemies[i]->Update(enemies[i]->getSprite().getPosition().x - pushAmount,
                                       enemies[i]->getSprite().getPosition().y);
                    enemies[j]->Update(enemies[j]->getSprite().getPosition().x + pushAmount,
                                       enemies[j]->getSprite().getPosition().y);
                    moved = true;
                }
            }
        }
        maxIterations--;
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
            if (turnDelayClock.getElapsedTime().asSeconds() < 2.5f)
            return;

            int hpBefore = player.getHealth();
            for (auto const& enemy : enemies) {
                if (player.getHealth() > 0)
                    enemy->Attack(player);
            }
            int totalDamageTaken = hpBefore - player.getHealth();

            if (totalDamageTaken > 0) {
                sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
                sf::Vector2f headPos(playerBounds.left + playerBounds.width / 2.f, playerBounds.top + 25.f);
                msgManager->add("-" + std::to_string(totalDamageTaken), MessageType::Damage, 1.5f, sf::Color::Red, headPos, 25.f);
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
        msgManager->add("DEFEAT!", MessageType::GameInfo, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("Victoria  has   fallen...", MessageType::GameInfo, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
        currentState = TurnState::GameOver;
        return true;
    }
    // Brak wrogow na arenie
    if (enemies.empty() && currentWave >= maxWaves) {
        msgManager->add("VICTORY!", MessageType::GameInfo, 15.0f, Theme::Text, Theme::CenterOfScreen, 60);
        msgManager->add("All  enemies  vanquished!", MessageType::GameInfo, 15.0f, Theme::Text, Theme::CenterOfScreen, 30);
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
        auto it = std::find_if(enemies.begin(), enemies.end(), [&](Enemy* e) {
            return e->getSprite().getGlobalBounds().contains(mouseCoord);
            });

            if (it != enemies.end()) {
                selectedEnemy = *it;
                isPlayerSelected = false;
            }
    }
}

void Arena::ExecuteAttack(AttackType attackType) {
    if (!selectedEnemy) return;

    int enemyHpBefore = selectedEnemy->getHealth();
    int playerHpBefore = player.getHealth();

    player.Hit(*selectedEnemy, attackType);
    int damageDealt = enemyHpBefore - selectedEnemy->getHealth();
    int playerHpLoss = playerHpBefore - player.getHealth();

    if (damageDealt > 0) {
        sf::FloatRect enemyBounds = selectedEnemy->getSprite().getGlobalBounds();
        sf::Vector2f enemyHeadPos(enemyBounds.left + enemyBounds.width / 2.f, enemyBounds.top + 40.f);

        msgManager->add("-" + std::to_string(damageDealt), MessageType::Damage, 1.5f, sf::Color::Red, enemyHeadPos, 25.f);
    }
    else {
        sf::FloatRect enemyBounds = selectedEnemy->getSprite().getGlobalBounds();
        sf::Vector2f enemyHeadPos(enemyBounds.left + enemyBounds.width / 2.f, enemyBounds.top + 40.f);

        msgManager->add("MISS", MessageType::Damage, 1.2f, sf::Color::Red, enemyHeadPos, 25.f);
    }
    if (playerHpLoss > 0) {
        sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();
        sf::Vector2f playerHeadPos(playerBounds.left + playerBounds.width / 2.f, playerBounds.top + 25.f);

        msgManager->add("-" + std::to_string(playerHpLoss), MessageType::Damage, 1.5f, sf::Color::Red, playerHeadPos, 25.f);
    }

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
    auto firstDead = std::stable_partition(enemies.begin(), enemies.end(), [](Enemy* enemy) {
        return !enemy->isDead();
    });
    std::for_each(firstDead, enemies.end(), [this](Enemy* deadEnemy) {
        int earnedPoints = deadEnemy->getPoints();
        battlePointsForHeal += earnedPoints;

        EnemyTypes deadEnemyType = deadEnemy->getType();
        float difficultyMultiplier = Stats::difMultipliers.at(Stats::difficulty);
        int enemyMaxHp = static_cast<int>(Stats::enemy.at(deadEnemyType).health * difficultyMultiplier);

        int earnedBattlePoints = static_cast<int>(enemyMaxHp * 1.25f);
        if (earnedBattlePoints < 20) earnedBattlePoints = 20;
        battlePointsForHeal += earnedBattlePoints;

        player.setGold(player.getGold() + deadEnemy->getGold());
        msgManager->add("Enemy defeated! +" + std::to_string(earnedPoints) + " Points", MessageType::Success, 2.0f);
        if (deadEnemy == selectedEnemy) {
            selectedEnemy = nullptr;
        }
        delete deadEnemy;
    });
    enemies.erase(firstDead, enemies.end());

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
        msgManager->add("Wave " + std::to_string(currentWave) + " starts!", MessageType::GameInfo, 2.5f, Theme::Text, Theme::CenterOfScreen, 60);
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
            int neededPoints = static_cast<int>(150 * Stats::difMultipliers.at(Stats::difficulty));
        if (battlePointsForHeal >= neededPoints) {
            int hpBefore = player.getHealth();
            player.Heal(35);
            int healedAmount = player.getHealth() - hpBefore;

            if (healedAmount > 0) {
                sf::FloatRect bounds = player.getSprite().getGlobalBounds();
                sf::Vector2f playerHeadPos(bounds.left + bounds.width / 2.f, bounds.top + 40.f);

                msgManager->add("+" + std::to_string(healedAmount), MessageType::Heal, 1.5f, sf::Color::Green, playerHeadPos, 25.f);
            }
            battlePointsForHeal -= neededPoints;
            isPlayerSelected = false;
            currentState = TurnState::EnemiesTurn;
            turnDelayClock.restart();
    } else {
        int missingPoints = neededPoints - battlePointsForHeal;
        msgManager->add("Need " + std::to_string(missingPoints) + " more Battle Points", MessageType::Error, 2.0f);
        isPlayerSelected = false;
    }
        }
    }
    Fight(); // Logika walki
    return true;
}

void Arena::Draw(sf::RenderWindow& window){
    // Rysowanie Areny
    window.draw(arenaBackGround);
    // Rysowanie Przeciwnikow
    for(auto const& enemy : enemies){
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

    float rightEdge = arenaBackGround.getTexture() ? arenaBackGround.getTexture()->getSize().x : 800.f;

     //Rysowanie licznika zlota
    sf::Text goldText;
    goldText.setFont(menagers.tex.getMainFont());
    goldText.setCharacterSize(20);
    Utils::ObjectFormatter<sf::Text>::formatText(goldText);
    goldText.setString("Gold: " + std::to_string(player.getGold()) + " G");

    float goldWidth = goldText.getLocalBounds().width;
    goldText.setPosition(rightEdge - goldWidth - 20.f, 30.f);
    window.draw(goldText);

    //Rysowanie licznika punktow
    int neededPoints = static_cast<int>(150 * Stats::difMultipliers.at(Stats::difficulty));

    sf::Text pointsText;
    pointsText.setFont(menagers.tex.getMainFont());
    pointsText.setCharacterSize(20);
    Utils::ObjectFormatter<sf::Text>::formatText(pointsText);
    pointsText.setString("Points: " + std::to_string(battlePointsForHeal) + " / " + std::to_string(neededPoints));

    float pointsWidth = pointsText.getLocalBounds().width;
    pointsText.setPosition(rightEdge - pointsWidth - 20.f, 65.f);
    window.draw(pointsText);

    msgManager->Draw(window);
}



