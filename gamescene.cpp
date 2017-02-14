#include "gamescene.h"
#include <QDebug>
#include <tower.h>

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
    , mp_TileSize(TileSize)
    , mp_Width(Width)
    , mp_Height(Height)
{
    setSceneRect(0, 0, Width, Height);
}

QPoint GameScene::mapGlobalToTile(QPoint GloalPos)
{
    return QPoint( GloalPos.x() / mp_TileSize, GloalPos.y() / mp_TileSize);
}

QPoint GameScene::mapTileToGlobal(QPoint TilePos)
{
    return QPoint( TilePos.x() * mp_TileSize, TilePos.y() * mp_TileSize);
}

void GameScene::AddGameItem(QGraphicsItem *Item, QPoint TilePos)
{
    addItem(Item);
    QPoint GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());
}

void GameScene::AddMesh()
{
    auto MeshWidth = mp_Width / mp_TileSize;
    auto MeshHeight = mp_Height / mp_TileSize;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            qDebug() << xMesh * mp_TileSize << ' ' << yMesh * mp_TileSize;
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , (xMesh + 1) * mp_TileSize, yMesh * mp_TileSize, QPen(QColor(255, 0, 0, 100))));
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , xMesh * mp_TileSize, (yMesh + 1) * mp_TileSize, QPen(QColor(255, 0, 0, 100))));
        }
    }
}

void GameScene::RemoveMesh()
{
    while (!mp_MeshLines.empty())
    {
        removeItem(mp_MeshLines.first());
        mp_MeshLines.pop_front();
    }
}
