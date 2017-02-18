#ifndef AMMO_H
#define AMMO_H

#include <QGraphicsPixmapItem>
#include "generalutils.h"

class Tower;
class QGraphicsItem;
class Enemy;

class Ammo : public QGraphicsPixmapItem
{
public:
    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Ammo };

    int getPower() const;
    const QPointF &getStartPos() const;
    int getRange() const;
    Enemy *getTarget() const;

    void InitRotation();
    void Update();

    int type() const;

private:
    friend class Tower;
    Ammo(Tower *TowerItem, Enemy *Target);

    // Tower that made shot
    Tower *mp_Tower;
    int mp_Power;
    QPointF mp_StartPos;
    int mp_Range;
    Enemy *mp_Target;

    constexpr static int mcp_Step = 8;
};

#endif // AMMO_H
