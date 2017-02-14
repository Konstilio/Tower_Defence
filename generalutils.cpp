#include "generalutils.h"
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>

GeneralUtils::GeneralUtils()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    if (rec.width() >= 1400)
    {
        mp_GameViewSize = QSize(1200, 800);
        mp_TileSize = 40;
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

const QPixmap &GeneralUtils::TiledTreeTowerPixmap()
{
    return GetTiledBitmap(mp_TiledTreeTowerPixmap, ":/Images/tree.png");
}

const QPixmap &GeneralUtils::TiledAcidTowerPixmap()
{
    return GetTiledBitmap(mp_TiledAcidTowerPixmap, ":/Images/acidtower.png");
}

const QPixmap &GeneralUtils::TiledIceTowerPixmap()
{
    return GetTiledBitmap(mp_TiledIceTowerPixmap, ":/Images/icetower.png");
}

const QPixmap &GeneralUtils::TiledStoneTowerPixmap()
{
    return GetTiledBitmap(mp_TiledStoneTowerPixmap, ":/Images/stonetower.png");
}

const QPixmap &GeneralUtils::AmmoPixmap()
{
    if (mp_AmmoPixmap.isNull())
        mp_AmmoPixmap = QPixmap(":/Images/ammo.png");

    return mp_AmmoPixmap;
}

QSize GeneralUtils::GameViewSize() const
{
    return mp_GameViewSize;
}

int GeneralUtils::TileSize() const
{
    return mp_TileSize;
}

const QPixmap& GeneralUtils::GetTiledBitmap(QPixmap &CachedPixMap, const QString &Path)
{
    if (CachedPixMap.isNull())
    {
        QPixmap temp = QPixmap(Path);
        CachedPixMap = temp.scaled(mp_TileSize, mp_TileSize);
    }

    return CachedPixMap;
}


