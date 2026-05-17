#pragma once
#include "zombie.h"

Zombie::Zombie(TextureMenager& textures) : Enemy(textures){
    enemySprite.setTexture(textures.getZombie());
    name = "Zombie";
    gold = 20;
    points = 100;
}

