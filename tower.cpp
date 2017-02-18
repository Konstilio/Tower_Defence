#include "tower.h"
#include "generalutils.h"
#include "generalutils.h"
#include "ammo.h"
#include <QBrush>
#include <QPen>

// Tower

Tower::Tower(QGraphicsItem *Parent)
    : QObject(), QGraphicsPixmapItem(Parent)
{

}

void Tower::InitRange()
{
    int RectSize = boundingRect().width();
    qreal Radius = getRange() * RectSize;
    qreal Size = (2 * getRange() + 1) * RectSize;
    mp_RangeCircle = new QGraphicsEllipseItem(-Radius, -Radius, Size, Size, this);
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

void Tower::Upgrade()
{
    delete mp_RangeCircle;

    setPixmap(GeneralUtils::Instance().TiledSuperiorTowerPixmap());
    mp_Range = 3;
    mp_Power = 6;
    InitRange();
    mp_Upgraded = true;
}

int Tower::getRange() const
{
    return mp_Range;
}

int Tower::getPower() const
{
    return mp_Power;
}

int Tower::getUpgradeCost() const
{
    return 100;
}

int Tower::getSellCost() const
{
    return 0.75 * getCost();
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

Ammo *Tower::ShootAmmo()
{
    Q_ASSERT(CanShoot());
    Ammo *Result = new Ammo(this, mp_Target);
    if (mp_Upgraded)
        Result->setPixmap(GeneralUtils::Instance().AmmoAcidPixmap());
    else
        Result->setPixmap(AmmoPixmap());

    return Result;
}

// Tower Factory

Tower *TowerFactory::Create(int towerId)
{
    Tower *Result = nullptr;
    if (towerId == Tower::ETowerId_Tree)
        Result = new TreeTower();
    else if (towerId == Tower::ETowerId_Acid)
        Result = new AcidTower();
    else if (towerId == Tower::ETowerId_Ice)
        Result = new IceTower();
    else if (towerId == Tower::ETowerId_Stone)
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

bool TreeTower::CanBeUpgraded() const
{
    return false;
}

QPixmap TreeTower::AmmoPixmap() const
{
    return QPixmap();
}

// AcidTower

AcidTower::AcidTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledAcidTowerPixmap());
    mp_Range = 2;
    mp_Power = 1;
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

bool AcidTower::CanBeUpgraded() const
{
    return true;
}

QPixmap AcidTower::AmmoPixmap() const
{
    return GeneralUtils::Instance().AmmoAcidPixmap();
}

// IceTower

IceTower::IceTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledIceTowerPixmap());
    mp_Range = 2;
    mp_Power = 2;
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

bool IceTower::CanBeUpgraded() const
{
    return true;
}

QPixmap IceTower::AmmoPixmap() const
{
    return GeneralUtils::Instance().AmmoIcePixmap();
}


// StoneTower

StoneTower::StoneTower(QGraphicsItem *Parent)
    : Tower(Parent)
{
    setPixmap(GeneralUtils::Instance().TiledStoneTowerPixmap());
    mp_Range = 2;
    mp_Power = 3;
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

bool StoneTower::CanBeUpgraded() const
{
    return true;
}

QPixmap StoneTower::AmmoPixmap() const
{
    return GeneralUtils::Instance().AmmoStonePixmap();
}

