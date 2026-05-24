#pragma once
#include "enemy.h"

class Boss : public Enemy{
public:
    Boss(TextureMenager& textures);
    void HpBarUpdate() override;
    void Draw(sf::RenderWindow& window) override;
};

