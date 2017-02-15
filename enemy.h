#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include "generalutils.h"

class Enemy : public QGraphicsPixmapItem
{
public:
    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Enemy };

    Enemy(QGraphicsItem *Parent = 0);

    virtual int getBonus() const = 0;
    virtual int getSpeed() const = 0;
    virtual int getHealth() const = 0;

    int type() const;

    void Update();
    void setTarget(const QPointF &Target);
    QPointF Center();

private:
    QPointF mp_Target;

};

class EnemyFactory
{
public:
    static Enemy *Create(int EnemyId);
};

class OutcastEnemy : public Enemy
{
public:
    OutcastEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;
    int getHealth() const override;

    int static getId();
};

class OutlawEnemy : public Enemy
{
public:
    OutlawEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;
    int getHealth() const override;

    int static getId();
};

class KatanamenEnemy : public Enemy
{
public:
    KatanamenEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;
    int getHealth() const override;

    int static getId();
};

#endif // ENEMY_H