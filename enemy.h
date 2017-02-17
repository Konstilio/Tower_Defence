#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include "generalutils.h"
class Ammo;

class Enemy : public QGraphicsPixmapItem
{
public:
    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Enemy };

    Enemy(QGraphicsItem *Parent = 0);

    virtual int getBonus() const = 0;
    virtual int getSpeed() const = 0;
    int getHealth() const;

    int type() const;

    // Returns true if close to TargetPoint
    bool Update();

    void setTargetPos(const QPointF &Target);
    const QPointF &getTargetPoint();

    bool Shooted(const Ammo *AmmoItem);
    QPointF Center();

protected:
    int mp_Health = 0;

private:
    QPointF mp_TargetPos;

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

    int static getId();
};

class OutlawEnemy : public Enemy
{
public:
    OutlawEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;

    int static getId();
};

class KatanamenEnemy : public Enemy
{
public:
    KatanamenEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;

    int static getId();
};

#endif // ENEMY_H
