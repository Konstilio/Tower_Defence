#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QSet>
#include "tilegraph.h"

class Tower;
class QTimer;
class Ammo;
class Enemy;
class Level;

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
    void StartGame();

signals:
    void SceneUpdated();
    void LevelChanged(Level *CurrentLevel);

private:
    void InitUpdateTimer();
    void InitEndPoints();

    // Tower updation
    void UpdateTowerTargetOnEnemy(Enemy *EnemyItem);
    void TowerShoot(Tower *TowerItem);

    // Ammo, Enemy Updates
    void RemoveOutOfRangeAmmos();
    void AddEnemy();
    void UpdateAmmoEnemyCollisions();
    void MoveEnemies();

    // Mesh
    void InitMesh();

private slots:
    void Update();

private:
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
    ShortestPathResult mp_DijkstraResult;

    QPointF mp_StartGlobalPos;
    QPointF mp_EndGlobalPos;
    QPoint mp_StartTilePos;
    QPoint mp_EndTilePos;

    Level* mp_Level = nullptr;
};

#endif // GAMESCENE_H
