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
        {ArmorsTypes::Basic,{100}},
        {ArmorsTypes::Steel,{300}},
        {ArmorsTypes::Goddess,{1000}}
    };

    inline const std::map<SwordsTypes, ItemStats> sword{
        {SwordsTypes::Basic,{20}},
        {SwordsTypes::Steel,{60}},
        {SwordsTypes::Goddess,{200}}
    };

    inline const std::map<EnemyTypes, EnemyStats> enemy{
        {EnemyTypes::Skeleton, {35,8}},
        {EnemyTypes::Zombie, {65,12}},
        {EnemyTypes::Mage, {120,25}},
        {EnemyTypes::Boss, {600,55}}
    };
}
