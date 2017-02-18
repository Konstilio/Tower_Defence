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
        mp_TileSize = 30;
    }
    else if (rec.width() >= 1000)
    {
         mp_GameViewSize = QSize(900, 600);
         mp_TileSize = 30;
    }
    else
    {
         mp_GameViewSize = QSize(600, 400);
         mp_TileSize = 20;
    }
}

GeneralUtils &GeneralUtils::Instance()
{
    static GeneralUtils utils;
    return utils;
}

const QPixmap &GeneralUtils::TiledTreeTowerPixmap() const
{
    return GetTiledBitmap(mp_TiledTreeTowerPixmap, ":/Images/tree.png");
}

const QPixmap &GeneralUtils::TiledAcidTowerPixmap() const
{
    return GetTiledBitmap(mp_TiledAcidTowerPixmap, ":/Images/acidtower.png");
}

const QPixmap &GeneralUtils::TiledIceTowerPixmap() const
{
    return GetTiledBitmap(mp_TiledIceTowerPixmap, ":/Images/icetower.png");
}

const QPixmap &GeneralUtils::TiledStoneTowerPixmap() const
{
    return GetTiledBitmap(mp_TiledStoneTowerPixmap, ":/Images/stonetower.png");
}

const QPixmap &GeneralUtils::TiledSuperiorTowerPixmap() const
{
    return GetTiledBitmap(mp_TiledSuperiorTowerPixmap, ":/Images/superiortower.png");
}

const QPixmap &GeneralUtils::AmmoPixmap() const
{
    if (mp_AmmoPixmap.isNull())
        mp_AmmoPixmap = QPixmap(":/Images/ammo.png");

    return mp_AmmoPixmap;
}

const QPixmap &GeneralUtils::TiledStartPixmap() const
{
    return GetTiledBitmap(mp_TiledStartPixmap, ":/Images/starting.png");
}

const QPixmap &GeneralUtils::TiledEndPixmap() const
{
     return GetTiledBitmap(mp_TiledEndPixmap, ":/Images/ending.png");
}

const QPixmap &GeneralUtils::TiledOutcastEnemyPixmap() const
{
    return GetTiledBitmap(mp_TiledOutcastEnemyPixmap, ":/Images/mightyoutcast.png");
}

const QPixmap &GeneralUtils::TiledOutlawEnemyPixmap() const
{
    return GetTiledBitmap(mp_TiledOutlawEnemyPixmap, ":/Images/outlaw.png");
}

const QPixmap &GeneralUtils::TiledKatanamenEnemyPixmap() const
{
    return GetTiledBitmap(mp_TiledKatanamenEnemyPixmap, ":/Images/royalkatanamen.png");
}

QSize GeneralUtils::GameViewSize() const
{
    return mp_GameViewSize;
}

int GeneralUtils::TileSize() const
{
    return mp_TileSize;
}

const QPixmap& GeneralUtils::GetTiledBitmap(QPixmap &CachedPixMap, const QString &Path) const
{
    if (CachedPixMap.isNull())
    {
        QPixmap temp = QPixmap(Path);
        CachedPixMap = temp.scaled(mp_TileSize, mp_TileSize);
    }

    return CachedPixMap;
}


