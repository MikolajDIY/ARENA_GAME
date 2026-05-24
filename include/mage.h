#pragma once
#include "enemy.h"

class Mage : public Enemy{
public:
    Mage(TextureMenager& textures);
    void HpBarUpdate() override;
};
