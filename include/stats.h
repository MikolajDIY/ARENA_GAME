#pragma once
#include "enemy.h"
#include "item.h"

// STATYSTYKI BITEWNE - Przykladowe

enum class Difficulties{easy,medium,hard};
namespace Stats{
    inline Difficulties difficulty= Difficulties::medium;

    inline const std::map<Difficulties,float> difMultipliers{
    {Difficulties::easy,0.75},
    {Difficulties::medium,1},
    {Difficulties::hard,1.5}
    };
    inline const std::map<ArmorsTypes, ItemStats> armor{
        {ArmorsTypes::Basic,{10}},
        {ArmorsTypes::Steel,{30}},
        {ArmorsTypes::Godness,{100}}
    };

    inline const std::map<SwordsTypes, ItemStats> sword{
        {SwordsTypes::Basic,{100}},
        {SwordsTypes::Steel,{300}},
        {SwordsTypes::Godness,{1000}}
    };

    inline const std::map<EnemyTypes, EnemyStats> enemy{
        {EnemyTypes::Skeleton, {10,5}},
        {EnemyTypes::Zombie, {30,5}},
        {EnemyTypes::Mage, {150,20}},
        {EnemyTypes::Boss, {1000,200}}
    };
}
