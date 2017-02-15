#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QSet>
#include "tilegraph.h"
#include "level.h"

class Tower;
class QTimer;
class Ammo;
class Enemy;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(int Width, int Height, int TileSize, QObject *Parent = Q_NULLPTR);
    QPoint mapGlobalToTile(const QPointF &GloalPos) const;
    QPointF mapTileToGlobal(const QPoint &TilePos) const;
    QPointF mapTileToGlobalCenter(const QPoint &TilePos) const;

    void AddTempGameItem(QGraphicsItem *Item, QPoint TilePos);

    // Next functions assumes that tower already added to scene as temp object
    void BuildTower(Tower *TowerItem);
    bool CanBuildTower(Tower *TowerItem) const;

    // Mesh
    void ShowMesh();
    void HideMesh();

public slots:
    void Update();

signals:
    void SceneUpdated();

private:
    void InitUpdateTimer();
    void InitEndPoints();

    // Tower updation
    void UpdateTowerTargetOnEnemy(Enemy *EnemyItem);
    void TowerShoot(Tower *TowerItem);

    // Ammo Updates
    void RemoveOutOfRangeAmmos();

    void AddEnemy();

    // Mesh
    void InitMesh();

    int mp_TileSize;
    int mp_Width;
    int mp_Height;
    int mp_TilesWidth;
    int mp_TilesHeight;

    QTimer *mp_UpdateTimer = nullptr;

    // Cashes
    QList<QGraphicsLineItem *> mp_MeshLines;
    QSet<Tower *> mp_Towers;
    QSet<Ammo *> mp_Ammos;
    QSet<Enemy *> mp_Enemies;
    QHash<QPoint, QSet<Tower *>> mp_PoseToTowerRange;

    TileGraph mp_Graph;

    QPointF mp_StartGlobalPos;
    QPointF mp_EndGlobalPos;
    QPoint mp_StartTilePos;
    QPoint mp_EndTilePos;

    LevelSettings mp_LevelSettings;
};

#endif // GAMESCENE_H
