#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QSet>

class Tower;
class QTimer;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(int Width, int Height, int TileSize, QObject *Parent = Q_NULLPTR);
    QPoint mapGlobalToTile(QPoint GloalPos);
    QPoint mapTileToGlobal(QPoint TilePos);

    void AddTempGameItem(QGraphicsItem *Item, QPoint TilePos);
    void AddMesh();
    void RemoveMesh();

    void CacheTower(Tower *TowerItem);

public slots:
    void Update();

private:
    void InitUpdateTimer();
    void TowerShoot(Tower *TowerItem);

    int mp_TileSize;
    int mp_Width;
    int mp_Height;

    QTimer *mp_UpdateTimer = nullptr;

    QList<QGraphicsLineItem *> mp_MeshLines;
    QSet<Tower *> mp_Towers;
};

#endif // GAMESCENE_H
