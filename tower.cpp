#include "tower.h"

Tower::Tower(const QPixmap &Pixmap, QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Pixmap, Parent)
{

}

RedTower::RedTower(const QPixmap &Pixmap, QGraphicsItem *Parent)
    : Tower(Pixmap, Parent)
{

}

int RedTower::getRange() const
{
    return 1;
}

int RedTower::getPower() const
{
    return 1;
}

int RedTower::getCost() const
{
    return 100;
}
