#ifndef AMMO_H
#define AMMO_H

#include <QGraphicsPixmapItem>
#include "generalutils.h"

class Tower;
class QGraphicsItem;

class Ammo : public QGraphicsPixmapItem
{
public:
    // For Qt purposes
    enum { Type = UserType + ECustomItemRole_Ammo };

    Ammo(Tower *TowerItem, QGraphicsItem *Parent = 0);
    int getPower() const;

private:
    Tower *mp_Tower; // Tower that made shot
};

#endif // AMMO_H
