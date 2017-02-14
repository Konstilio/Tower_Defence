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

    void addGameItem(QGraphicsItem *Item, QPoint TilePos);

private:
    int mp_TileSize;
};

#endif // GAMESCENE_H
