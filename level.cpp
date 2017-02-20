#include "level.h"

Level::Level(QObject *Parent)
    : QObject(Parent)
    , mp_Generator(mp_RandomDevice())
    , mp_Distribution({mp_ProbabilityOutlaw, mp_ProbabilityOutcast, mp_ProbabilityKatanamen})
{
    mp_EnemyCurrentTicks = 5;
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

bool Level::KillEnemy()
{
    ++mp_OverallKilledEnemies;
    return ++mp_KilledLevelEnemies >= mp_LevelEnemies;
}

int Level::getKilledEnemies() const
{
    return mp_OverallKilledEnemies;
}

EnemyFactory::EEnemy Level::GenerateEnemyId() const
{
    return static_cast<EnemyFactory::EEnemy>(mp_Distribution(mp_Generator) + 1);
}

int Level::getLifes() const
{
    return mp_Lifes;
}

void Level::IncLifes(int Lifes)
{
    mp_Lifes -= Lifes;
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

bool Level::NextLevel()
{
    if (++mp_LevelNumber < mcp_MaxLevel + 1)
    {
        // Reset enemies
        mp_LevelEnemies += 5;
        mp_KilledLevelEnemies = 0;
        mp_MaxEnemies += 5;

        // Reset ticks
        mp_EnemyTicks -= 6;
        mp_EnemyCurrentTicks = mp_EnemyTicks;

        // Reset Probabilities
        mp_ProbabilityOutlaw -= mp_ProbabilityRatio;
        mp_ProbabilityOutcast += mp_ProbabilityRatioHalf;
        mp_ProbabilityKatanamen += mp_ProbabilityRatioHalf;
        mp_Distribution.param({mp_ProbabilityOutlaw, mp_ProbabilityOutcast, mp_ProbabilityKatanamen});

        // Add costs
        mp_Costs += 5;

        return false;
    }

    return true;
}
