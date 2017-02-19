#include "generalutils.h"
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

GeneralUtils::GeneralUtils()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    if (rec.width() >= 1400)
    {
        mp_GameViewSize = QSize(1200, 900);
        mp_TileSize = 50;
        mp_AmmoSize = 10;
    }
    else //if (rec.width() >= 1000)
    {
         mp_GameViewSize = QSize(800, 600);
         mp_TileSize = 40;
         mp_AmmoSize = 10;
    }
// Not tested
//    else
//    {
//         mp_GameViewSize = QSize(600, 400);
//         mp_TileSize = 20;
//         mp_AmmoSize = 6;
//    }
}

GeneralUtils &GeneralUtils::Instance()
{
    static GeneralUtils utils;
    return utils;
}

const QPixmap &GeneralUtils::TiledTreeTowerPixmap() const
{
    return getTiledBitmap(mp_TiledTreeTowerPixmap, ":/Images/treetower");
}

const QPixmap &GeneralUtils::TiledAcidTowerPixmap() const
{
    return getTiledBitmap(mp_TiledAcidTowerPixmap, ":/Images/acidtower");
}

const QPixmap &GeneralUtils::TiledIceTowerPixmap() const
{
    return getTiledBitmap(mp_TiledIceTowerPixmap, ":/Images/icetower");
}

const QPixmap &GeneralUtils::TiledStoneTowerPixmap() const
{
    return getTiledBitmap(mp_TiledStoneTowerPixmap, ":/Images/stonetower");
}

const QPixmap &GeneralUtils::TiledSuperiorTowerPixmap() const
{
    return getTiledBitmap(mp_TiledSuperiorTowerPixmap, ":/Images/superioir");
}

const QPixmap &GeneralUtils::AmmoAcidPixmap() const
{
    return getAmmoBitmap(mp_AmmoAcidPixmap, ":/Images/ammo");
}

const QPixmap &GeneralUtils::AmmoIcePixmap() const
{
    return getAmmoBitmap(mp_AmmoIcePixmap, ":/Images/icecube");
}

const QPixmap &GeneralUtils::AmmoStonePixmap() const
{
    return getAmmoBitmap(mp_AmmoStonePixmap, ":/Images/stone");
}

const QPixmap &GeneralUtils::AmmoFirePixmap() const
{
    return getAmmoBitmap(mp_AmmoFirePixmap, ":/Images/fire");
}

const QPixmap &GeneralUtils::TiledStartPixmap() const
{
    return getTiledBitmap(mp_TiledStartPixmap, ":/Images/starting");
}

const QPixmap &GeneralUtils::TiledEndPixmap() const
{
     return getTiledBitmap(mp_TiledEndPixmap, ":/Images/ending");
}

const QPixmap &GeneralUtils::TiledOutcastEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledOutcastEnemyPixmap, ":/Images/outcast");
}

const QPixmap &GeneralUtils::TiledOutlawEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledOutlawEnemyPixmap, ":/Images/outlaw");
}

const QPixmap &GeneralUtils::TiledKatanamenEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledKatanamenEnemyPixmap, ":/Images/katanamen");
}

QSize GeneralUtils::GameViewSize() const
{
    return mp_GameViewSize;
}

int GeneralUtils::TileSize() const
{
    return mp_TileSize;
}

const QPixmap& GeneralUtils::getTiledBitmap(QPixmap &CachedPixMap, const QString &Path) const
{
    if (CachedPixMap.isNull())
        CachedPixMap = QPixmap(Path + QString::number(mp_TileSize) + ".png");

    return CachedPixMap;
}

const QPixmap &GeneralUtils::getAmmoBitmap(QPixmap &CachedPixMap, const QString &Path) const
{
    if (CachedPixMap.isNull())
        CachedPixMap = QPixmap(Path + QString::number(mp_AmmoSize) + ".png");

    return CachedPixMap;
}


