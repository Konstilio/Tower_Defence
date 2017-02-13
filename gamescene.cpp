#include "gamescene.h"
#include <QDebug>
#include <tower.h>

GameScene::GameScene(int Width, int Height, int MeshWidth, int MeshHeight, QObject *Parent)
    : QGraphicsScene(Parent)
{
    setSceneRect(0, 0, Width, Height);

    auto TileWidth = Width / MeshWidth;
    auto TileHeight = Height / MeshHeight;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            qDebug() << xMesh * TileWidth << ' ' << yMesh * TileHeight;
            addLine(xMesh * TileWidth, yMesh * TileHeight , (xMesh + 1) * TileWidth, yMesh * TileHeight, QPen(QColor(255, 0, 0, 100)));
            addLine(xMesh * TileWidth, yMesh * TileHeight , xMesh * TileWidth, (yMesh + 1) * TileHeight, QPen(QColor(255, 0, 0, 100)));
        }
    }

    RedTower *Tower = new RedTower(QPixmap(":/Images/RedTower.png"));
    addItem(Tower);
    Tower->setX(0);
    Tower->setY(0);
}
