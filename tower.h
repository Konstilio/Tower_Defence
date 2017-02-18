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

    enum ETowerId
    {
        ETowerId_Tree = 1
        , ETowerId_Acid = 2
        , ETowerId_Ice = 3
        , ETowerId_Stone = 4
        , ETowerId_Superior = 5
        , ETowerId_Upgrade = 100
        , ETowerId_Sell = 200
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
    void Upgrade();

    int getRange() const;
    int getPower() const;
    virtual int getCost() const = 0;
    virtual int getShootTicks() const = 0;
    virtual bool CanShoot() const = 0;
    virtual bool CanBeUpgraded() const = 0;
    int getUpgradeCost() const;

    int type() const;
    QPointF Center() const;
    qreal getRangeRadius() const;

protected:
    QGraphicsEllipseItem *mp_RangeCircle = nullptr;
    int mp_ShootTicks = 0;
    bool mp_HaveTarget = false;

    // Enemy target to shoot
    Enemy *mp_Target;

    // Radius in global coordintares from tower center
    qreal mp_RangeRadius = 0.;

    // Properties
    int  mp_Range = 0;
    int  mp_Power = 0;
};

class TowerFactory
{
public:
    Tower static *Create(int towerId);
};

class TreeTower : public Tower
{
private:
    friend class TowerFactory;
    TreeTower(QGraphicsItem *Parent = 0);

public:

    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;
    bool CanBeUpgraded() const override;
};

class AcidTower : public Tower
{
private:
    friend class TowerFactory;
    AcidTower(QGraphicsItem *Parent = 0);

public:
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;
    bool CanBeUpgraded() const override;
};

class IceTower : public Tower
{
private:
    friend class TowerFactory;
    IceTower(QGraphicsItem *Parent = 0);

public:
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;
    bool CanBeUpgraded() const override;
};

class StoneTower : public Tower
{
private:
    friend class TowerFactory;
    StoneTower(QGraphicsItem *Parent = 0);

public:
    int getCost()  const override;
    int getShootTicks() const override;
    bool CanShoot() const override;
    bool CanBeUpgraded() const override;
};


#endif // TOWER_H
