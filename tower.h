#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>


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
    enum { Type = UserType + 1 };

    Tower(QGraphicsItem *Parent = 0);
    void InitRange();
    void Indicate(EIndicator Indicator);
    void ClearIndicator();

    virtual int getRange() const = 0;
    virtual int getPower() const = 0;
    virtual int getCost() const = 0;
    virtual bool canShoot() const = 0;

    int type() const;

protected:
    QGraphicsEllipseItem *mp_RangeCircle = nullptr;
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
    bool canShoot() const override;

    int static getId();
};

class AcidTower : public Tower
{
public:
    AcidTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    bool canShoot() const override;

    int static getId();
};

class IceTower : public Tower
{
public:
    IceTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    bool canShoot() const override;

    int static getId();
};

class StoneTower : public Tower
{
public:
    StoneTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
    bool canShoot() const override;

    int static getId();
};


#endif // TOWER_H
