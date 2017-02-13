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
};

class RedTower : public Tower
{
public:
    RedTower(QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;

    int static getId();
};

#endif // TOWER_H
