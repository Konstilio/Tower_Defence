#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include "generalutils.h"
class Ammo;

class Enemy : public QObject, public QGraphicsPixmapItem
{
public:
    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Enemy };

    enum ESpeed
    {
        ESpeed_Slow = 1
        , ESpeed_Medium = 2
        , ESpeed_Fast = 3
    };

    Enemy(QGraphicsItem *Parent = 0);
    ~Enemy();

    virtual int getBonus() const = 0;
    virtual int getSpeed() const = 0;
    int getHealth() const;
    int getInitialHealth() const;

    int type() const;

    // Returns true if close to TargetPoint
    bool Update();

    void setTargetPos(const QPointF &Target);
    const QPointF &getTargetPoint();

    bool Shooted(const Ammo *AmmoItem);
    QPointF Center();

protected:
    int mp_Health = 0;
    int mp_InitialHealth = 0;

private:
    QPointF mp_TargetPos;

};

class EnemyFactory
{
public:
    enum EEnemy
    {
        EEnemy_Outcast = 1
        , EEnemy_Outlaw = 2
        , EEnemy_Katanamen = 3
    };

    static Enemy *Create(EEnemy EnemyId);
};

class OutcastEnemy : public Enemy
{
public:
    OutcastEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;

};

class OutlawEnemy : public Enemy
{
public:
    OutlawEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;

};

class KatanamenEnemy : public Enemy
{
public:
    KatanamenEnemy(QGraphicsItem *Parent = 0);

    int getBonus() const override;
    int getSpeed()  const override;
};

#endif // ENEMY_H
