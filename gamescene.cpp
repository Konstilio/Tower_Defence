#include "gamescene.h"
#include <QDebug>
#include <tower.h>

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
{
    setSceneRect(0, 0, Width, Height);
    QPixmap pim(":/Images/sand_template.jpg");
    setBackgroundBrush(pim.scaled(Width, Height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

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

    RedTower *Tower = new RedTower();
    addItem(Tower);
    Tower->setX(0);
    Tower->setY(0);
}
