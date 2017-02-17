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
    int RectSize = boundingRect().width();
    qreal Radius = getRange() * RectSize;
    qreal Size = (2 * getRange() + 1) * RectSize;
    mp_RangeCircle = new QGraphicsEllipseItem(x() - Radius, y() - Radius, Size, Size, this);
    mp_RangeCircle->setPen(QPen(CanShoot() ? QColor(255, 255, 255, 200) : QColor(0, 0, 0, 0)));
    mp_RangeRadius = mp_RangeCircle->boundingRect().width() / 2;
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

bool Tower::ReadyShoot()
{
    if (--mp_ShootTicks == 0)
    {
        ResetShootTicks();
        return true;
    }

    return false;
}

void Tower::ResetShootTicks()
{
    mp_ShootTicks = getShootTicks();
}

bool Tower::getHaveTarget() const
{
    return mp_HaveTarget;
}

Enemy *Tower::getTarget() const
{
    return mp_Target;
}

void Tower::AqcuireTarget(Enemy *Target)
{
    mp_HaveTarget = true;
    mp_Target = Target;
}

void Tower::ReleaseTarget()
{
    mp_HaveTarget = false;
}

QList<QGraphicsItem *> Tower::TowerCollidingItems()
{
    return collidingItems();
}

QList<QGraphicsItem *> Tower::RangeCollidingItems()
{
    return mp_RangeCircle->collidingItems();
}

int Tower::type() const
{
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
}

QPointF Tower::Center() const
{
    auto Size = GeneralUtils::Instance().TileSize();
    return { x() + Size/ 2, y() + Size / 2 };
}

qreal Tower::getRangeRadius() const
{
    return mp_RangeRadius;
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
    Result->ResetShootTicks();
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
    return 5;
}

int TreeTower::getShootTicks() const
{
    return 0;
}

bool TreeTower::CanShoot() const
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
    return 1;
}

int AcidTower::getCost() const
{
    return 10;
}

int AcidTower::getShootTicks() const
{
    return 10;
}

bool AcidTower::CanShoot() const
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
    return 20;
}

int IceTower::getShootTicks() const
{
    return 10;
}

bool IceTower::CanShoot() const
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
    return 3;
}

int StoneTower::getCost() const
{
    return 20;
}

int StoneTower::getShootTicks() const
{
    return 15;
}

bool StoneTower::CanShoot() const
{
    return true;
}

int StoneTower::getId()
{
    return 4;
}
