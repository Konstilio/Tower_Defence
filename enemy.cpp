#include "enemy.h"
#include "generalutils.h"
#include <qmath.h>

// Enemy

Enemy::Enemy(QGraphicsItem *Parent)
    : QGraphicsPixmapItem(Parent)
{

}

int Enemy::type() const
{
    return Type;
}

void Enemy::Update()
{
    auto alpha = rotation();
    qreal dy = getSpeed() * qSin(qDegreesToRadians(alpha));
    qreal dx = getSpeed() * qCos(qDegreesToRadians(alpha));

    setPos(x() + dx, y() + dy);
}

void Enemy::setTarget(const QPointF &Target)
{
    mp_Target = Target;
    QLineF ln(pos(), mp_Target);
    setRotation(-1. * ln.angle());
}

QPointF Enemy::Center()
{
    return {x() + GeneralUtils::Instance().TileSize() / 2, y() + GeneralUtils::Instance().TileSize() / 2};
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

int OutcastEnemy::getHealth() const
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

int OutlawEnemy::getHealth() const
{
    return 3;
}

int OutlawEnemy::getId()
{
    return 2;
}

// KatanamenEnemy

KatanamenEnemy::KatanamenEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
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

int KatanamenEnemy::getHealth() const
{
    return 1;
}

int KatanamenEnemy::getId()
{
    return 3;
}

