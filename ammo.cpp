#include "ammo.h"
#include "tower.h"
#include <qmath.h>
#include <QLine>
#include "enemy.h"

Ammo::Ammo(Tower *TowerItem, Enemy *Target, QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
    , mp_Tower(TowerItem)
    , mp_Target(Target)
    , mp_Power(TowerItem->getPower())
    , mp_StartPos(TowerItem->Center())
    , mp_Range(TowerItem->getRange())
{
    setPixmap(GeneralUtils::Instance().AmmoPixmap());
}

int Ammo::getPower() const
{
    return mp_Power;
}

const QPointF &Ammo::getStartPos() const
{
    return mp_StartPos;
}

int Ammo::getRange() const
{
    return mp_Range;
}

Enemy *Ammo::getTarget() const
{
    return mp_Target;
}

void Ammo::InitRotation()
{
    QLineF ln(pos(), mp_Target->Center());
    setRotation(-1. * ln.angle());
}

void Ammo::Update()
{
    auto alpha = rotation();
    qreal dy = mcp_Step  * qSin(qDegreesToRadians(alpha));
    qreal dx = mcp_Step  * qCos(qDegreesToRadians(alpha));

    setPos(x() + dx, y() + dy);
}

int Ammo::type() const
{
    return Type;
}

