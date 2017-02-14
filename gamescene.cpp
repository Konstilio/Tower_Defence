#include "gamescene.h"
#include <QDebug>
#include <tower.h>

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
    , mp_TileSize(TileSize)
{
    setSceneRect(0, 0, Width, Height);
    QPixmap bcg(":/Images/sandbackground.jpg");
    setBackgroundBrush(bcg.scaled(Width, Height, Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    auto MeshWidth = Width / TileSize;
    auto MeshHeight = Height / TileSize;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            qDebug() << xMesh * TileSize << ' ' << yMesh * TileSize;
            addLine(xMesh * TileSize, yMesh * TileSize , (xMesh + 1) * TileSize, yMesh * TileSize, QPen(QColor(255, 0, 0, 100)));
            addLine(xMesh * TileSize, yMesh * TileSize , xMesh * TileSize, (yMesh + 1) * TileSize, QPen(QColor(255, 0, 0, 100)));
        }
    }

    TreeTower *Tower = new TreeTower();
    addItem(Tower);
    Tower->setX(0);
    Tower->setY(0);
}

QPoint GameScene::mapGlobalToTile(QPoint GloalPos)
{
    return QPoint( GloalPos.x() / mp_TileSize, GloalPos.y() / mp_TileSize);
}

QPoint GameScene::mapTileToGlobal(QPoint TilePos)
{
    return QPoint( TilePos.x() * mp_TileSize, TilePos.y() * mp_TileSize);
}

void GameScene::addGameItem(QGraphicsItem *Item, QPoint TilePos)
{
    addItem(Item);
    QPoint GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());
}
