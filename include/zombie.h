#pragma once
#include "enemy.h"

class Zombie : public Enemy{
public:
    Zombie(TextureMenager& textures);
    void HpBarUpdate() override;
};

