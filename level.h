#ifndef LEVEL_H
#define LEVEL_H

struct LevelSettings
{
    // Enemy
    int m_MaxEnemies = 20;
    int m_EnemyTicks = 80;
};

class Level
{
public:
    Level();
};

#endif // LEVEL_H
