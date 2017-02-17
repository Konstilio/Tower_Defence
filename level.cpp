#include "level.h"

Level::Level(QObject *Parent)
    : QObject(Parent)
{

}

int Level::getMaxEnemies() const
{
    return mp_MaxEnemies;
}

int Level::IncEnemyTicks()
{
    int Res = --mp_EnemyCurrentTicks;
    if (Res == 0)
        mp_EnemyCurrentTicks = mp_EnemyTicks;
    return Res;
}

int Level::getLifes() const
{
    return mp_Lifes;
}

void Level::IncLifes()
{
    --mp_Lifes;
}

int Level::getCosts() const
{
    return mp_Costs;
}

void Level::AddCosts(int costs)
{
    mp_Costs += costs;
}

void Level::ReduceCosts(int costs)
{
    mp_Costs -= costs;
}

int Level::getLevelNumber()
{
    return mp_LevelNumber;
}

void Level::NextLevel()
{
    ++mp_LevelNumber;
}
