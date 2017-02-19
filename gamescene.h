#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QSet>
#include <QPointer>
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
    ~GameScene();

    QPoint mapGlobalToTile(const QPointF &GloalPos) const;
    QPointF mapTileToGlobal(const QPoint &TilePos) const;
    QPointF mapTileToGlobalCenter(const QPoint &TilePos) const;

    void AddTempGameItem(QGraphicsItem *Item, QPoint TilePos);
    void RemoveTempItem(QGraphicsItem *Item);
    void MoveTempItem(QGraphicsItem *Item, QPoint TilePos);

    // Towers
    bool CanBuildTower(Tower *TowerItem) const;
    bool CanUpgradeTower(Tower *TowerItem) const;
    void UpgradeTower(Tower *TowerItem);
    void SellTower(Tower *TowerItem);
    // BuildTower assumes that tower already added to scene as temp object
    void BuildTower(Tower *TowerItem);


    void StartGame();
    void PauseGame();
    void ResumeGame();

signals:
    void SceneUpdated();
    void LevelChanged(QPointer<Level> CurrentLevel);

private:
    void ResetUpdateTimer();
    void InitEndPoints();
    // Mesh
    void InitMesh();

// Update
    // Tower updation
    void UpdateTowerTargets();
    void UpdateTowerTargetOnEnemy(Enemy *EnemyItem);
    void TowerShoot(Tower *TowerItem);

    // Ammo, Enemy Updates
    void RemoveOutOfRangeAmmos();
    void AddEnemy();
    void UpdateAmmoEnemyCollisions();
    void RemoveReachedEnemies();
    void MoveEnemies();
    void KillEnemy(Enemy *EnemyItem);
//

    // CacheUpdates
    void UpdateTowerPosesCache(Tower *TowerItem, bool Add);

private slots:
    void Update();

private:
    int mp_TileSize;
    int mp_Width;
    int mp_Height;
    int mp_TilesWidth;
    int mp_TilesHeight;

    QTimer *mp_UpdateTimer = nullptr;
    static constexpr int mpc_UpdateTimerInterval = 40;

    // Caches
    QSet<Tower *> mp_Towers;
    QSet<Ammo *> mp_Ammos;
    QSet<Enemy *> mp_Enemies;
    QHash<QPoint, QSet<Tower *>> mp_PoseToTowerRange;
    void ResetCache();

    // Graph 
    Tile *mp_TempTile = nullptr;
    TileGraph mp_Graph;
    ShortestPathResult mp_PathResult; // Path Result that doesn't consider temp Tiles
    ShortestPathResult mp_TempPathResult; // Path Result that does consider temp Tiles

    QPointF mp_StartGlobalPos;
    QPointF mp_EndGlobalPos;
    QPoint mp_StartTilePos;
    QPoint mp_EndTilePos;

    Level* mp_Level = nullptr;

    // Limit sending scene updated signals
    int mp_UpdateSignalTicks = 12;
    int IncUpdateSignal();
};

#endif // GAMESCENE_H
