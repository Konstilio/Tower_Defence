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

QPixmap GeneralUtils::TiledTreeTowerPixmap()
{
    if (mp_TiledRedTowerPixmap.isNull())
    {
        QPixmap temp = QPixmap(":/Images/tree.png");
        mp_TiledRedTowerPixmap = temp.scaled(mp_TileSize, mp_TileSize);
    }

    return mp_TiledRedTowerPixmap;
}

QSize GeneralUtils::GameViewSize() const
{
    return mp_GameViewSize;
}

int GeneralUtils::TileSize() const
{
    return mp_TileSize;
}


