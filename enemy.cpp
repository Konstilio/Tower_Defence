#include "enemy.h"
#include "ammo.h"
#include "generalutils.h"
#include <qmath.h>
#include <cmath>
#include <QLineF>
#include <QDebug>

// Enemy

Enemy::Enemy(QGraphicsItem *Parent)
    : QObject(), QGraphicsPixmapItem(Parent)
{

}

Enemy::~Enemy()
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

int Enemy::getInitialHealth() const
{
    return mp_InitialHealth;
}

bool Enemy::Update()
{
    auto alpha = rotation();
    int dy = std::round(getSpeed() * qSin(qDegreesToRadians(alpha)));
    int dx = std::round(getSpeed() * qCos(qDegreesToRadians(alpha)));

    // we use int here to avoid negative value that makes item non visible
    setPos(x() + dx, y() + dy);

    QLineF Line(pos(), mp_TargetPos);
    return Line.length() < 0.1;
}

void Enemy::setTargetPos(const QPointF &Target)
{
    mp_TargetPos = Target;
    QLineF ln(pos(), mp_TargetPos);
    setRotation(-1. * ln.angle());
}

const QPointF &Enemy::getTargetPoint()
{
    return mp_TargetPos;
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
Enemy *EnemyFactory::Create(EEnemy EnemyId)
{
    Enemy *Result = nullptr;
    if (EnemyId == EEnemy_Outcast)
        Result = new OutcastEnemy();
    else if (EnemyId == EEnemy_Outlaw)
        Result = new OutlawEnemy();
    else if (EnemyId == EEnemy_Katanamen)
        Result = new KatanamenEnemy();
    else
        Q_ASSERT(false);

    Result->setTransformOriginPoint(Result->boundingRect().width() / 2, Result->boundingRect().height() / 2);
    return Result;
}

// OutcastEnemy

OutcastEnemy::OutcastEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_InitialHealth = 30;
    mp_Health = mp_InitialHealth;
    setPixmap(GeneralUtils::Instance().TiledOutcastEnemyPixmap());
}

int OutcastEnemy::getBonus() const
{
    return 1;
}

int OutcastEnemy::getSpeed() const
{
    return ESpeed_Slow;
}

// OutlawEnemy

OutlawEnemy::OutlawEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_InitialHealth = 90;
    mp_Health = mp_InitialHealth;
    setPixmap(GeneralUtils::Instance().TiledOutlawEnemyPixmap());
}

int OutlawEnemy::getBonus() const
{
    return 3;
}

int OutlawEnemy::getSpeed() const
{
    return ESpeed_Slow;
}

// KatanamenEnemy

KatanamenEnemy::KatanamenEnemy(QGraphicsItem *Parent)
    : Enemy(Parent)
{
    mp_InitialHealth = 30;
    mp_Health = mp_InitialHealth;
    setPixmap(GeneralUtils::Instance().TiledKatanamenEnemyPixmap());
}

int KatanamenEnemy::getBonus() const
{
    return 4;
}

int KatanamenEnemy::getSpeed() const
{
    return ESpeed_Fast;
}

