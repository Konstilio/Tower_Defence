#include "ammo.h"
#include "tower.h"

Ammo::Ammo(Tower *TowerItem, QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
    , mp_Tower(TowerItem)
{
    setPixmap(GeneralUtils::Instance().AmmoPixmap());
}

int Ammo::getPower() const
{
    return mp_Tower->getPower();
}

