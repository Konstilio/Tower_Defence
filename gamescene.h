#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>

class GameScene : public QGraphicsScene
{
public:
    GameScene(int Width, int Height, int TileSize, QObject *Parent = Q_NULLPTR);
    QPoint mapGlobalToTile(QPoint GloalPos);
    QPoint mapTileToGlobal(QPoint TilePos);

    void AddGameItem(QGraphicsItem *Item, QPoint TilePos);
    void AddMesh();
    void RemoveMesh();

private:
    int mp_TileSize;
    int mp_Width;
    int mp_Height;
    QList<QGraphicsLineItem *> mp_MeshLines;
};

#endif // GAMESCENE_H
