#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>

class Level : public QObject
{
public:
    Level(QObject *Parent = 0);

    // Enemies
    int getMaxEnemies() const;
    int IncEnemyTicks();

    // User
    int getLifes() const;
    void IncLifes();
    int getCosts() const;
    void AddCosts(int costs);
    void ReduceCosts(int costs);

    // General
    int getLevelNumber();
    void NextLevel();

private:
    // Enemies
    int mp_MaxEnemies = 20;
    int mp_EnemyTicks = 80;
    int mp_EnemyCurrentTicks = 80;

    // User
    int mp_Lifes = 20;
    int mp_Costs = 100;

    // General
    int mp_LevelNumber = 1;
};

#endif // LEVEL_H
