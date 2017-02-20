#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include "enemy.h"
#include <random>

class Level : public QObject
{
public:
    Level(QObject *Parent = 0);

    // Enemies
    int getMaxEnemies() const;
    int IncEnemyTicks();
    bool KillEnemy(); // returns true if needs next level
    int getKilledEnemies() const;
    EnemyFactory::EEnemy GenerateEnemyId() const;

    // User
    int getLifes() const;
    void IncLifes(int Lifes);
    int getCosts() const;
    void AddCosts(int costs);
    void ReduceCosts(int costs);

    // General
    int getLevelNumber();
    bool NextLevel(); // returns true if game won

private:
    // Enemies
    int mp_MaxEnemies = 10;
    int mp_EnemyTicks = 120;
    int mp_EnemyCurrentTicks = 0;
    int mp_LevelEnemies = 10; // 1 Level needs 20 killed enemies
    int mp_OverallKilledEnemies = 0;
    int mp_KilledLevelEnemies = 0;

    // Enemy Generation
    std::random_device mp_RandomDevice;
    mutable std::mt19937 mp_Generator;
    double mp_ProbabilityOutlaw = 0.8;
    double mp_ProbabilityOutcast = 0.15;
    double mp_ProbabilityKatanamen = 0.05;
    static constexpr double mp_ProbabilityRatio = 0.08;
    static constexpr double mp_ProbabilityRatioHalf = 0.04;
    mutable std::discrete_distribution<> mp_Distribution;

    // User
    int mp_Lifes = 20;
    int mp_Costs = 100;

    // General
    int mp_LevelNumber = 1;
    static int constexpr mcp_MaxLevel = 10;

};

#endif // LEVEL_H
