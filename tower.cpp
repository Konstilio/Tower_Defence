#include "tower.h"
#include "generalutils.h"

// Tower

Tower::Tower(QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
{

}

// Tower Factory

Tower *TowerFactory::Create(int towerId)
{
    if (towerId == TreeTower::getId())
        return new TreeTower();
    else
        Q_ASSERT(false);
}

// Red Tower

TreeTower::TreeTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledTreeTowerPixmap());
}

int TreeTower::getRange() const
{
    return 1;
}

int TreeTower::getPower() const
{
    return 1;
}

int TreeTower::getCost() const
{
    return 100;
}

bool TreeTower::canShoot() const
{
    return true;
}

int TreeTower::getId()
{
    return 1;
}
