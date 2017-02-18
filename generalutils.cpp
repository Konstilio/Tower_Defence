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
        mp_TileSize = 40;
        mp_AmmoSize = 10;
    }
    else if (rec.width() >= 1000)
    {
         mp_GameViewSize = QSize(900, 600);
         mp_TileSize = 30;
         mp_AmmoSize = 8;
    }
    else
    {
         mp_GameViewSize = QSize(600, 400);
         mp_TileSize = 20;
         mp_AmmoSize = 6;
    }
}

GeneralUtils &GeneralUtils::Instance()
{
    static GeneralUtils utils;
    return utils;
}

const QPixmap &GeneralUtils::TiledTreeTowerPixmap() const
{
    return getTiledBitmap(mp_TiledTreeTowerPixmap, ":/Images/tree.png");
}

const QPixmap &GeneralUtils::TiledAcidTowerPixmap() const
{
    return getTiledBitmap(mp_TiledAcidTowerPixmap, ":/Images/acidtower.png");
}

const QPixmap &GeneralUtils::TiledIceTowerPixmap() const
{
    return getTiledBitmap(mp_TiledIceTowerPixmap, ":/Images/icetower.png");
}

const QPixmap &GeneralUtils::TiledStoneTowerPixmap() const
{
    return getTiledBitmap(mp_TiledStoneTowerPixmap, ":/Images/stonetower.png");
}

const QPixmap &GeneralUtils::TiledSuperiorTowerPixmap() const
{
    return getTiledBitmap(mp_TiledSuperiorTowerPixmap, ":/Images/superiortower.png");
}

const QPixmap &GeneralUtils::AmmoAcidPixmap() const
{
    return getAmmoBitmap(mp_AmmoAcidPixmap, ":/Images/ammo.png");
}

const QPixmap &GeneralUtils::AmmoIcePixmap() const
{
    return getAmmoBitmap(mp_AmmoIcePixmap, ":/Images/icecube10.png");
}

const QPixmap &GeneralUtils::AmmoStonePixmap() const
{
    return getAmmoBitmap(mp_AmmoStonePixmap, ":/Images/stone10.png");
}

const QPixmap &GeneralUtils::TiledStartPixmap() const
{
    return getTiledBitmap(mp_TiledStartPixmap, ":/Images/starting.png");
}

const QPixmap &GeneralUtils::TiledEndPixmap() const
{
     return getTiledBitmap(mp_TiledEndPixmap, ":/Images/ending.png");
}

const QPixmap &GeneralUtils::TiledOutcastEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledOutcastEnemyPixmap, ":/Images/mightyoutcast.png");
}

const QPixmap &GeneralUtils::TiledOutlawEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledOutlawEnemyPixmap, ":/Images/outlaw.png");
}

const QPixmap &GeneralUtils::TiledKatanamenEnemyPixmap() const
{
    return getTiledBitmap(mp_TiledKatanamenEnemyPixmap, ":/Images/royalkatanamen.png");
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
    {
        QPixmap temp = QPixmap(Path);
        CachedPixMap = temp.scaled(mp_TileSize, mp_TileSize);
    }

    return CachedPixMap;
}

const QPixmap &GeneralUtils::getAmmoBitmap(QPixmap &CachedPixMap, const QString &Path) const
{
    if (CachedPixMap.isNull())
    {
        QPixmap temp = QPixmap(Path);
        CachedPixMap = temp.scaled(mp_AmmoSize, mp_AmmoSize);
    }

    return CachedPixMap;
}


