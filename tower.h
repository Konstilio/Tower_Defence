#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>
#include "generalutils.h"

class Enemy;

class Tower : public QGraphicsPixmapItem
{
public:
    enum EIndicator
    {
        EIndicator_CanBuild
        , EIndicator_CanNotBuild
        , EIndicator_Select
    };

    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Tower };

    Tower(QGraphicsItem *Parent = 0);
    void InitRange();
    void Indicate(EIndicator Indicator);
    void ClearIndicator();
    bool ReadyShoot();
    void ResetShootTicks();

    bool getHaveTarget() const;
    Enemy *getTarget() const;
    void AqcuireTarget(Enemy *Target);
    void ReleaseTarget();

    QList<QGraphicsItem *> TowerCollidingItems();
    QList<QGraphicsItem *> RangeCollidingItems();

    virtual int getRange() const = 0;
    virtual int getPower() const = 0;
    virtual int getCost() const = 0;
    virtual int getShootTicks() const = 0;
    virtual bool CanShoot() const = 0;

    int type() const;
    QPointF Center() const;

protected:
    QGraphicsEllipseItem *mp_RangeCircle = nullptr;
    int mp_ShootTicks = 0;
    bool mp_HaveTarget = false;
    Enemy *mp_Target;
};

class TowerFactory
{
public:
    Tower static *Create(int towerId);
};

class TreeTower : public Tower
{
public:
    TreeTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;

    int static getId();
};

class AcidTower : public Tower
{
public:
    AcidTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;

    int static getId();
};

class IceTower : public Tower
{
public:
    IceTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;

    int static getId();
};

class StoneTower : public Tower
{
public:
    StoneTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;

    int static getId();
};


#endif // TOWER_H
