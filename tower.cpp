#include "tower.h"
#include "generalutils.h"

// Tower

Tower::Tower(QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
{

}

// Red Tower

RedTower::RedTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledRedTowerPixmap());
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

int RedTower::getId()
{
    return 1;
}
