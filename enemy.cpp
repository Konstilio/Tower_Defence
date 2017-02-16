#include "enemy.h"
#include "ammo.h"
#include "generalutils.h"
#include <qmath.h>

// Enemy

Enemy::Enemy(QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
{

}

// Needed For QT
int Enemy::type() const
{
    return Type;
}

int Enemy::getHealth() const
{
    return mp_Health;
}

void Enemy::Update()
{
    auto alpha = rotation();
    qreal dy = getSpeed() * qSin(qDegreesToRadians(alpha));
    qreal dx = getSpeed() * qCos(qDegreesToRadians(alpha));

    setPos(x() + dx, y() + dy);
}

void Enemy::setTargetPoint(const QPointF &Target)
{
    mp_TargetPoint = Target;
    QLineF ln(pos(), mp_TargetPoint);
    setRotation(-1. * ln.angle());
}

bool Enemy::Shooted(const Ammo *AmmoItem)
{
    mp_Health -= AmmoItem->getPower();
    if (mp_Health <= 0)
        return true;

    return false;
}

QPointF Enemy::Center()
{
    return {x() + boundingRect().width() / 2, y() + boundingRect().height() / 2};
}

// Enemy Factory
Enemy *EnemyFactory::Create(int EnemyId)
{
    Enemy *Result = nullptr;
    if (EnemyId == OutcastEnemy::getId())
        Result = new OutcastEnemy();
    else if (EnemyId == OutlawEnemy::getId())
        Result = new OutlawEnemy();
    else if (EnemyId == KatanamenEnemy::getId())
        Result = new KatanamenEnemy();
    else
        Q_ASSERT(false);

    return Result;
}

// OutcastEnemy

OutcastEnemy::OutcastEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_Health = 5;
    setPixmap(GeneralUtils::Instance().TiledOutcastEnemyPixmap());
}

int OutcastEnemy::getBonus() const
{
    return 1;
}

int OutcastEnemy::getSpeed() const
{
    return 1;
}

int OutcastEnemy::getId()
{
    return 1;
}

// OutlawEnemy

OutlawEnemy::OutlawEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_Health = 15;
    setPixmap(GeneralUtils::Instance().TiledOutlawEnemyPixmap());
}

int OutlawEnemy::getBonus() const
{
    return 3;
}

int OutlawEnemy::getSpeed() const
{
    return 1;
}

int OutlawEnemy::getId()
{
    return 2;
}

// KatanamenEnemy

KatanamenEnemy::KatanamenEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_Health = 5;
    setPixmap(GeneralUtils::Instance().TiledKatanamenEnemyPixmap());
}

int KatanamenEnemy::getBonus() const
{
    return 3;
}

int KatanamenEnemy::getSpeed() const
{
    return 3;
}

int KatanamenEnemy::getId()
{
    return 3;
}

