#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>


class Tower : public QGraphicsPixmapItem
{
public:
    Tower(const QPixmap &Pixmap, QGraphicsItem *Parent = 0);

    virtual int getRange() const = 0;
    virtual int getPower() const = 0;
    virtual int getCost() const = 0;
};

class RedTower : public Tower
{
public:
    RedTower(const QPixmap &Pixmap, QGraphicsItem *Parent = 0);

    int getRange() const override;
    int getPower() const override;
    int getCost()  const override;
};

#endif // TOWER_H
