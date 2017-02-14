#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>


class Tower : public QGraphicsPixmapItem
{
public:
    Tower(QGraphicsItem *Parent = 0);

    virtual int getRange() const = 0;
    virtual int getPower() const = 0;
    virtual int getCost() const = 0;
    virtual bool canShoot() const = 0;
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

#endif // TOWER_H
