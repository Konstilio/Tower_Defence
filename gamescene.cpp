#include "gamescene.h"
#include <QDebug>
#include "tower.h"
#include "ammo.h"
#include <QTimer>
#include <QElapsedTimer>
#include "generalutils.h"
#include "enemy.h"

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
    , mp_TileSize(TileSize)
    , mp_Width(Width)
    , mp_Height(Height)
    , mp_TilesWidth(mp_Width / mp_TileSize)
    , mp_TilesHeight (mp_Height / mp_TileSize)
    , mp_Graph(mp_TilesWidth, mp_TilesHeight)
{
    setSceneRect(0, 0, Width, Height);
    InitEndPoints();
    InitMesh();
    InitUpdateTimer();
}

QPoint GameScene::mapGlobalToTile(const QPointF &GloalPos) const
{
    return QPoint( GloalPos.x() / mp_TileSize, GloalPos.y() / mp_TileSize);
}

QPointF GameScene::mapTileToGlobal(const QPoint &TilePos) const
{
    return QPoint( TilePos.x() * mp_TileSize, TilePos.y() * mp_TileSize);
}

QPointF GameScene::mapTileToGlobalCenter(const QPoint &TilePos) const
{
     return QPoint( TilePos.x() * mp_TileSize + mp_TileSize / 2, TilePos.y() * mp_TileSize + mp_TileSize / 2);
}

void GameScene::AddTempGameItem(QGraphicsItem *Item, QPoint TilePos)
{
    addItem(Item);
    QPointF GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());
}

void GameScene::InitMesh()
{
    auto MeshWidth = mp_Width / mp_TileSize;
    auto MeshHeight = mp_Height / mp_TileSize;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            qDebug() << xMesh * mp_TileSize << ' ' << yMesh * mp_TileSize;
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , (xMesh + 1) * mp_TileSize, yMesh * mp_TileSize, QPen(QColor(255, 255, 255, 30))));
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , xMesh * mp_TileSize, (yMesh + 1) * mp_TileSize, QPen(QColor(255, 255, 255, 30))));
        }
    }

    HideMesh();
}

void GameScene::ShowMesh()
{
    for (auto *iMeshLine : mp_MeshLines)
        iMeshLine->show();
}

void GameScene::HideMesh()
{
    //for (auto *iMeshLine : mp_MeshLines)
        //iMeshLine->hide();
}

void GameScene::BuildTower(Tower *TowerItem)
{
    QPoint TilePos = mapGlobalToTile(TowerItem->pos());
    mp_Graph.getTile(TilePos).setType(Tile::EType_Busy);
    mp_Towers.insert(TowerItem);

    QSet<const Tile *> Neighbours;
    mp_Graph.getLogicNeighbours(TilePos, TowerItem->getRange(), Neighbours);
    for (const auto *Neighbour : Neighbours)
    {
        QPoint RangePoint(Neighbour->getX(), Neighbour->getY());
        mp_PoseToTowerRange[RangePoint].insert(TowerItem);
    }
}

bool GameScene::CanBuildTower(Tower *TowerItem) const
{
    QElapsedTimer timer;
    timer.start();

    // First check tiles
    QPoint TilePos = mapGlobalToTile(TowerItem->pos());
    if (!mp_Graph.getTile(TilePos).getType() == Tile::EType_Empty)
        return false;

    // Check Distance to ends
    if (TileGraph::MaxTileDistance(TilePos, mp_StartTilePos) <= 1 || TileGraph::MaxTileDistance(TilePos, mp_EndTilePos) <= 1)
        return false;

    // Check Enemies since they are not part of graph
    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
    {
        QPoint EnemyTilePos = mapGlobalToTile((*iEnemy)->pos());
        if (TileGraph::MaxTileDistance(TilePos, EnemyTilePos) <= 1)
            return false;
    }

    qDebug() << "CanBuildTower() took " << timer.elapsed() << " ms " << "Enemies: " << mp_Enemies.size();
    return true;
}

void GameScene::Update()
{
    QElapsedTimer timer;
    timer.start();

    AddEnemy();
    RemoveOutOfRangeAmmos();
    UpdateAmmoEnemyCollisions();

    // Release Target
    for (auto iTower = mp_Towers.cbegin(); iTower != mp_Towers.cend(); ++iTower)
        (*iTower)->ReleaseTarget();

    // Acquire Target for towers through enemies Cache
    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
        UpdateTowerTargetOnEnemy((*iEnemy));

    for (auto iTower = mp_Towers.cbegin(); iTower != mp_Towers.cend(); ++iTower)
         TowerShoot(*iTower);

    for (auto iAmmo = mp_Ammos.cbegin(); iAmmo != mp_Ammos.cend() ; ++iAmmo)
        (*iAmmo)->Update();

    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
        (*iEnemy)->Update();


    emit SceneUpdated();
    qDebug() << "Update() took " << timer.elapsed() << " ms " << "Ammos: " << mp_Ammos.size();

}

void GameScene::InitUpdateTimer()
{
    mp_UpdateTimer = new QTimer(this);
    connect(mp_UpdateTimer, &QTimer::timeout, this, &GameScene::Update);
    mp_UpdateTimer->start(25);
}

void GameScene::InitEndPoints()
{
    // Start
    QGraphicsPixmapItem *StartItem = new QGraphicsPixmapItem(GeneralUtils::Instance().TiledStartPixmap());
    addItem(StartItem);
    mp_StartTilePos = QPoint(0,0);
    mp_StartGlobalPos = mapTileToGlobal(mp_StartTilePos);
    StartItem->setX(mp_StartGlobalPos.x());
    StartItem->setY(mp_StartGlobalPos.y());
    mp_Graph.getTile(mp_StartTilePos).setType(Tile::EType_Start);

    // End
    QGraphicsPixmapItem *EndItem = new QGraphicsPixmapItem(GeneralUtils::Instance().TiledEndPixmap());
    addItem(EndItem);
    mp_EndTilePos = QPoint(mp_TilesWidth - 1, mp_TilesHeight - 1);
    mp_EndGlobalPos = mapTileToGlobal(mp_EndTilePos);
    EndItem->setX(mp_EndGlobalPos.x());
    EndItem->setY(mp_EndGlobalPos.y());
    mp_Graph.getTile(mp_EndTilePos).setType(Tile::EType_End);
}

void GameScene::UpdateTowerTargetOnEnemy(Enemy *EnemyItem)
{
    QPoint EnemyTilePos = mapGlobalToTile(EnemyItem->pos());
    QSet<Tower *> Towers = mp_PoseToTowerRange[EnemyTilePos];
    for (auto *TowerItem : Towers)
    {
        if (TowerItem->CanShoot() && !TowerItem->getHaveTarget())
            TowerItem->AqcuireTarget(EnemyItem);
    }
}

void GameScene::TowerShoot(Tower *TowerItem)
{
    if (!TowerItem->CanShoot())
        return;

    if (!TowerItem->ReadyShoot())
        return;

    if (!TowerItem->getHaveTarget())
        return;

    Ammo *AmmoItem = new Ammo(TowerItem, TowerItem->getTarget());
    addItem(AmmoItem);
    AmmoItem->setX(TowerItem->Center().x());
    AmmoItem->setY(TowerItem->Center().y());
    AmmoItem->InitRotation();
    mp_Ammos.insert(AmmoItem);
}

void GameScene::RemoveOutOfRangeAmmos()
{
    for (auto iAmmo = mp_Ammos.cbegin(); iAmmo != mp_Ammos.cend() ;)
    {
        Ammo *AmmoItem = *iAmmo;
        QLineF Line(AmmoItem->pos(), AmmoItem->getStartPos());
        if (Line.length() > AmmoItem->getRange() * GeneralUtils::Instance().TileSize())
        {
            auto iTemp = iAmmo++;
            removeItem(AmmoItem);
            mp_Ammos.erase(iTemp);
        }
        else
            ++iAmmo;
    }
}

void GameScene::AddEnemy()
{
    if (--mp_LevelSettings.m_EnemyTicks > 0)
        return;

    if (mp_Enemies.size() == mp_LevelSettings.m_MaxEnemies)
        return;

    Enemy *EnemyItem = EnemyFactory::Create(OutcastEnemy::getId());
    addItem(EnemyItem);
    EnemyItem->setX(mp_StartGlobalPos.x());
    EnemyItem->setY(mp_StartGlobalPos.y());
    EnemyItem->setTargetPoint(QPointF(mp_Width, 0));

    mp_Enemies.insert(EnemyItem);
    mp_LevelSettings.m_EnemyTicks = 80;
}

// Todo: maybe take rotation into account
void GameScene::UpdateAmmoEnemyCollisions()
{
    qDebug() << "UpdateAmmoEnemyCollisions begin: "  << mp_Enemies.size();
    for (auto iAmmo = mp_Ammos.cbegin(); iAmmo != mp_Ammos.cend() ;)
    {
        Ammo *AmmoItem = *iAmmo;
        Enemy *TargetEnemy = AmmoItem->getTarget();
        auto EnemyIt = mp_Enemies.find(TargetEnemy);

        // Check if target enemy exists
        if (EnemyIt == mp_Enemies.end())
        {
            // If not - delete this ammo
            auto iTemp = iAmmo++;
            removeItem(AmmoItem);
            mp_Ammos.erase(iTemp);
            continue;
        }

        // check whether ammo collides with enemy
        QRectF AmmoRect = AmmoItem->boundingRect();
        AmmoRect.moveTo(AmmoItem->pos());

        QRectF EnemyRect = TargetEnemy->boundingRect();
        EnemyRect.moveTo(TargetEnemy->pos());

        if (EnemyRect.intersects(AmmoRect))
        {
            if (TargetEnemy->Shooted(AmmoItem))
            {
                removeItem(TargetEnemy);
                mp_Enemies.erase(EnemyIt);
            }
        }

        ++iAmmo;
    }

    qDebug() << "UpdateAmmoEnemyCollisions end: "  << mp_Enemies.size();
}


