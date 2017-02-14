#include "tower.h"
#include "generalutils.h"
#include "generalutils.h"
#include <QBrush>
#include <QPen>

// Tower

Tower::Tower(QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
{

}

void Tower::InitRange()
{
    qreal radius = getRange() * GeneralUtils::Instance().TileSize();
    qreal size = (2 * getRange() + 1) * GeneralUtils::Instance().TileSize();
    mp_RangeCircle = new QGraphicsEllipseItem(x() - radius, y() - radius, size, size, this);
    mp_RangeCircle->setPen(QPen(canShoot() ? QColor(255, 255, 255, 200) : QColor(0, 0, 0, 0)));
}

void Tower::Indicate(Tower::EIndicator Indicator)
{

    QColor Color = [&]()
    {
        if (Indicator == EIndicator_CanBuild)
            return QColor(0, 255, 0, 80);
        else if (Indicator == EIndicator_CanNotBuild)
            return QColor(255, 0, 0, 80);
        else if (Indicator == EIndicator_Select)
            return QColor(255, 255, 255, 80);
        else
        {
            Q_ASSERT(false);
            return QColor();
        }
    }();

    mp_RangeCircle->setBrush(QBrush(Color, Qt::SolidPattern));
}

void Tower::ClearIndicator()
{
    mp_RangeCircle->setBrush(QBrush());
}

int Tower::type() const
{
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
}

// Tower Factory

Tower *TowerFactory::Create(int towerId)
{
    Tower *Result = nullptr;
    if (towerId == TreeTower::getId())
        Result = new TreeTower();
    else if (towerId == AcidTower::getId())
        Result = new AcidTower();
    else if (towerId == IceTower::getId())
        Result = new IceTower();
    else if (towerId == StoneTower::getId())
        Result = new StoneTower();
    else
        Q_ASSERT(false);

    Result->InitRange();
    return Result;
}

// TreeTower

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
    return false;
}

int TreeTower::getId()
{
    return 1;
}

// AcidTower

AcidTower::AcidTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledAcidTowerPixmap());
}

int AcidTower::getRange() const
{
    return 2;
}

int AcidTower::getPower() const
{
    return 2;
}

int AcidTower::getCost() const
{
    return 100;
}

bool AcidTower::canShoot() const
{
    return true;
}

int AcidTower::getId()
{
    return 2;
}

// IceTower

IceTower::IceTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledIceTowerPixmap());
}

int IceTower::getRange() const
{
    return 2;
}

int IceTower::getPower() const
{
    return 2;
}

int IceTower::getCost() const
{
    return 100;
}

bool IceTower::canShoot() const
{
    return true;
}

int IceTower::getId()
{
    return 3;
}

// StoneTower

StoneTower::StoneTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledStoneTowerPixmap());
}

int StoneTower::getRange() const
{
    return 2;
}

int StoneTower::getPower() const
{
    return 2;
}

int StoneTower::getCost() const
{
    return 100;
}

bool StoneTower::canShoot() const
{
    return true;
}

int StoneTower::getId()
{
    return 4;
}
