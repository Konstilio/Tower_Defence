#include "gamescene.h"
#include <QDebug>
#include "tower.h"
#include "ammo.h"
#include <QTimer>
#include <QElapsedTimer>
#include "generalutils.h"
#include "enemy.h"
#include "level.h"

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
    , mp_TileSize(TileSize)
    , mp_Width(Width)
    , mp_Height(Height)
    , mp_TilesWidth(mp_Width / mp_TileSize)
    , mp_TilesHeight (mp_Height / mp_TileSize)
{
    mp_UpdateSignalTicks = mpc_UpdateSignalTicks;
    setSceneRect(0, 0, Width, Height);
}

GameScene::~GameScene()
{
    clear();
}

QPoint GameScene::mapGlobalToTile(const QPointF &GloalPos) const
{
    return QPoint( GloalPos.x() / mp_TileSize, GloalPos.y() / mp_TileSize);
}

QPointF GameScene::mapTileToGlobal(const QPoint &TilePos) const
{
    return QPointF( TilePos.x() * mp_TileSize, TilePos.y() * mp_TileSize);
}

QPointF GameScene::mapTileToGlobalCenter(const QPoint &TilePos) const
{
     return QPointF( TilePos.x() * mp_TileSize + mp_TileSize / 2., TilePos.y() * mp_TileSize + mp_TileSize / 2.);
}

void GameScene::StartGame()
{
    clear();
    ResetCache();

    // Reset Level
    delete mp_Level;
    mp_Level = new Level(this);

    // Reset Graph
    mp_Graph = TileGraph(mp_TilesWidth, mp_TilesHeight);

    InitEndPoints();
    InitMesh();
    ResetUpdateTimer();

    mp_PathResult = mp_Graph.getShortestPathToDestination(mp_EndTilePos);

    emit LevelChanged(mp_Level);
}

void GameScene::PauseGame()
{
    mp_UpdateTimer->stop();
}

void GameScene::ResumeGame()
{
    mp_UpdateTimer->start(mpc_UpdateTimerInterval);
}

void GameScene::AddTempGameItem(QGraphicsItem *Item, QPoint TilePos)
{
    addItem(Item);
    QPointF GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());

    SetTempTile(TilePos);
}

void GameScene::RemoveTempItem(QGraphicsItem *Item)
{
    if (!mp_TempTile)
        return;

    removeItem(Item);
    if (mp_TempTile->getType() == Tile::EType_Temp)
        mp_TempTile->setType(Tile::EType_Empty);
    mp_TempTile = nullptr;
}

void GameScene::MoveTempItem(QGraphicsItem *Item, QPoint TilePos)
{
    QPointF GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());

    if (mp_TempTile->getType() == Tile::EType_Temp)
        mp_TempTile->setType(Tile::EType_Empty);

    SetTempTile(TilePos);
}

void GameScene::SetTempTile(const QPoint &TilePos)
{
    mp_TempTile = &mp_Graph.getTile(TilePos);
    if (mp_TempTile->getType() == Tile::EType_Empty)
    {
        mp_TempTile->setType(Tile::EType_Temp);
        mp_TempPathResult = mp_Graph.getShortestPathToDestination(mp_EndTilePos);
    }
}

void GameScene::InitMesh()
{
    auto MeshWidth = mp_Width / mp_TileSize;
    auto MeshHeight = mp_Height / mp_TileSize;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , (xMesh + 1) * mp_TileSize, yMesh * mp_TileSize, QPen(QColor(255, 255, 255, 30)));
            addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , xMesh * mp_TileSize, (yMesh + 1) * mp_TileSize, QPen(QColor(255, 255, 255, 30)));
        }
    }
}

void GameScene::UpdateTowerPosesCache(Tower *TowerItem, bool Add)
{
    Q_ASSERT(mp_Towers.contains(TowerItem));

    QPoint TilePos = mapGlobalToTile(TowerItem->pos());
    QSet<const Tile *> Neighbours;
    mp_Graph.getLogicNeighbours(TilePos, TowerItem->getRange(), Neighbours);
    for (const auto *Neighbour : Neighbours)
    {
        QPoint RangePoint(Neighbour->getX(), Neighbour->getY());
        if (Add)
            mp_PoseToTowerRange[RangePoint].insert(TowerItem);
        else
            mp_PoseToTowerRange[RangePoint].remove(TowerItem);
    }
}

void GameScene::BuildTower(Tower *TowerItem)
{
#ifdef QT_DEBUG
    QPoint TilePos = mapGlobalToTile(TowerItem->pos());
    Q_ASSERT(mp_TempTile);
    Tile *TowerTile = &mp_Graph.getTile(TilePos);
    Q_ASSERT(TowerTile == mp_TempTile);
#endif

    mp_TempTile->setType(Tile::EType_Busy);
    mp_TempTile = nullptr;

    mp_PathResult = std::move(mp_TempPathResult);

    mp_Towers.insert(TowerItem);

    UpdateTowerPosesCache(TowerItem, true);

    mp_Level->ReduceCosts(TowerItem->getCost());
    emit LevelChanged(mp_Level);
}

bool GameScene::CanBuildTower(Tower *TowerItem) const
{
    if (mp_Level->getCosts() < TowerItem->getCost())
        return false;

    // First check tiles
    QPoint TilePos = mapGlobalToTile(TowerItem->pos());
    if (!(mp_Graph.getTile(TilePos).getType() == Tile::EType_Temp))
        return false;

    // Check Distance to ends
    if (TileGraph::MaxTileDistance(TilePos, mp_StartTilePos) <= 1 || TileGraph::MaxTileDistance(TilePos, mp_EndTilePos) <= 1)
        return false;

    // Check if close to Enemy since they are not part of graph
    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
    {
        QPoint EnemyTilePos = mapGlobalToTile((*iEnemy)->pos());
        QPoint EnemyTargetTilePos = mapGlobalToTile((*iEnemy)->getTargetPoint());
        if (TileGraph::MaxTileDistance(TilePos, EnemyTilePos) < 1 || TileGraph::MaxTileDistance(TilePos, EnemyTargetTilePos) < 1)
            return false;
    }

    if (!mp_Graph.AllPathesExists(mp_TempPathResult))
        return false;

    return true;
}

bool GameScene::CanUpgradeTower(Tower *TowerItem) const
{
    Q_ASSERT(mp_Towers.contains(TowerItem));

    return TowerItem->CanBeUpgraded() && (mp_Level->getCosts() >= TowerItem->getUpgradeCost());
}

void GameScene::UpgradeTower(Tower *TowerItem)
{
    if (!CanUpgradeTower(TowerItem))
        return;

    // Remove old cache
    UpdateTowerPosesCache(TowerItem, false);

    TowerItem->Upgrade();

    // Add new cache
    UpdateTowerPosesCache(TowerItem, true);

    mp_Level->ReduceCosts(TowerItem->getUpgradeCost());
    emit LevelChanged(mp_Level);
}

void GameScene::SellTower(Tower *TowerItem)
{
    auto iTower = mp_Towers.find(TowerItem);
    if (iTower == mp_Towers.end())
        return;

    // Remove old cache
    UpdateTowerPosesCache(TowerItem, false);

    mp_Towers.erase(iTower);
    removeItem(TowerItem);
    mp_Level->AddCosts(TowerItem->getSellCost());
    emit LevelChanged(mp_Level);
    delete TowerItem;
}

void GameScene::Update()
{
    AddEnemy();
    RemoveOutOfRangeAmmos();
    UpdateAmmoEnemyCollisions();
    RemoveReachedEnemies();
    UpdateTowerTargets();
    TowersShoot();
    MoveAmmos();
    MoveEnemies();

    if (IncUpdateSignal() == 0)
        emit SceneUpdated();
}

void GameScene::ResetCache()
{
    mp_Towers.clear();
    mp_Ammos.clear();
    mp_Enemies.clear();
    mp_PoseToTowerRange.clear();
}

int GameScene::IncUpdateSignal()
{
    int Result = --mp_UpdateSignalTicks;
    if (mp_UpdateSignalTicks == 0)
        mp_UpdateSignalTicks = mpc_UpdateSignalTicks;
    return Result;
}

void GameScene::ResetUpdateTimer()
{
    delete mp_UpdateTimer;
    mp_UpdateTimer = new QTimer(this);
    connect(mp_UpdateTimer, &QTimer::timeout, this, &GameScene::Update);
    mp_UpdateTimer->start(mpc_UpdateTimerInterval);
}

void GameScene::InitEndPoints()
{
    // Start
    auto *StartItem = new QGraphicsPixmapItem(GeneralUtils::Instance().TiledStartPixmap());
    addItem(StartItem);
    mp_StartTilePos = QPoint(0,0);
    mp_StartGlobalPos = mapTileToGlobal(mp_StartTilePos);
    StartItem->setX(mp_StartGlobalPos.x());
    StartItem->setY(mp_StartGlobalPos.y());
    mp_Graph.getTile(mp_StartTilePos).setType(Tile::EType_Start);

    // End
    auto *EndTime = new QGraphicsPixmapItem(GeneralUtils::Instance().TiledEndPixmap());
    addItem(EndTime);
    mp_EndTilePos = QPoint(mp_TilesWidth - 1, mp_TilesHeight - 1);
    mp_EndGlobalPos = mapTileToGlobal(mp_EndTilePos);
    EndTime->setX(mp_EndGlobalPos.x());
    EndTime->setY(mp_EndGlobalPos.y());
    mp_Graph.getTile(mp_EndTilePos).setType(Tile::EType_End);
}

void GameScene::UpdateTowerTargets()
{
    // Release Targets
    for (auto iTower = mp_Towers.cbegin(); iTower != mp_Towers.cend(); ++iTower)
        (*iTower)->ReleaseTarget();

    // Acquire Target for towers through enemies Cache
    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
        UpdateTowerTargetOnEnemy((*iEnemy));
}

void GameScene::UpdateTowerTargetOnEnemy(Enemy *EnemyItem)
{
    QPoint EnemyTilePos = mapGlobalToTile(EnemyItem->pos());
    QSet<Tower *> Towers = mp_PoseToTowerRange[EnemyTilePos];
    for (auto *TowerItem : Towers)
    {
        if (TowerItem->CanShoot() && !TowerItem->getHaveTarget())
        {
            QLineF Line(TowerItem->Center(), EnemyItem->Center());
            if (Line.length() < TowerItem->getRangeRadius())
                TowerItem->AqcuireTarget(EnemyItem);
        }
    }
}

void GameScene::TowersShoot()
{
    for (auto iTower = mp_Towers.cbegin(); iTower != mp_Towers.cend(); ++iTower)
    {
        auto *TowerItem = *iTower;

        if (!TowerItem->CanShoot())
            continue;

        if (!TowerItem->ReadyShoot())
            continue;

        if (!TowerItem->getHaveTarget())
            continue;

        Ammo *AmmoItem = TowerItem->ShootAmmo();
        addItem(AmmoItem);
        AmmoItem->setX(TowerItem->Center().x());
        AmmoItem->setY(TowerItem->Center().y());
        AmmoItem->InitRotation();
        mp_Ammos.insert(AmmoItem);
    }
}

void GameScene::RemoveOutOfRangeAmmos()
{
    for (auto iAmmo = mp_Ammos.begin(); iAmmo != mp_Ammos.end() ;)
    {
        Ammo *AmmoItem = *iAmmo;
        QLineF Line(AmmoItem->pos(), AmmoItem->getStartPos());
        if (Line.length() > AmmoItem->getRange() * GeneralUtils::Instance().TileSize())
        {
            auto iTemp = iAmmo++;
            removeItem(AmmoItem);
            delete AmmoItem;
            mp_Ammos.erase(iTemp);
        }
        else
            ++iAmmo;
    }
}

void GameScene::AddEnemy()
{
    if (mp_Level->IncEnemyTicks() > 0)
        return;

    if (mp_Enemies.size() == mp_Level->getMaxEnemies())
        return;

    Enemy *EnemyItem = EnemyFactory::Create(mp_Level->GenerateEnemyId());
    addItem(EnemyItem);
    EnemyItem->setX(mp_StartGlobalPos.x());
    EnemyItem->setY(mp_StartGlobalPos.y());

    QPointF NextTarget = mapTileToGlobal(mp_Graph.getNextPathPoint(mp_StartTilePos, mp_PathResult));
    EnemyItem->setTargetPos(NextTarget);

    mp_Enemies.insert(EnemyItem);
}

// Todo: maybe take rotation into account
void GameScene::UpdateAmmoEnemyCollisions()
{
    auto RemoveAmmo = [&](QSet<Ammo *>::iterator &AmmoIt)
    {
        Ammo *AmmoItem = *AmmoIt;
        auto iTemp = AmmoIt++;
        removeItem(AmmoItem);
        delete AmmoItem;
        mp_Ammos.erase(iTemp);
    };

    for (auto iAmmo = mp_Ammos.begin(); iAmmo != mp_Ammos.end() ;)
    {
        Ammo *AmmoItem = *iAmmo;
        Enemy *TargetEnemy = AmmoItem->getTarget();

        if (mp_Enemies.find(TargetEnemy) == mp_Enemies.end())
        {
            // If not - delete this ammo
            RemoveAmmo(iAmmo);
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
                KillEnemy(TargetEnemy);

            RemoveAmmo(iAmmo);
            continue;
        }

        ++iAmmo;
    }
}

void GameScene::MoveAmmos()
{
    for (auto iAmmo = mp_Ammos.cbegin(); iAmmo != mp_Ammos.cend() ; ++iAmmo)
        (*iAmmo)->Update();
}

void GameScene::RemoveReachedEnemies()
{
    int Reached = 0;
    for (auto iEnemy = mp_Enemies.begin(); iEnemy != mp_Enemies.end() ;)
    {
        Enemy *EnemyItem = *iEnemy;
        QPointF EndPos = mapTileToGlobalCenter(mp_EndTilePos) ;
        QLineF Line(EnemyItem->Center(), EndPos);

        // Enemy reached the end
        if (Line.length() <= EnemyItem->getSpeed() / 2.)
        {
            ++Reached;
            removeItem(EnemyItem);
            auto iTemp = iEnemy++;
            mp_Enemies.erase(iTemp);
            delete EnemyItem;
            continue;
        }

        ++iEnemy;
    }

    if (Reached > 0)
    {
        mp_Level->IncLifes(Reached);
        emit LevelChanged(mp_Level);
        if (mp_Level->getLifes() <= 0)
            emit GameLost();
    }
}

void GameScene::MoveEnemies()
{
    for (auto iEnemy = mp_Enemies.cbegin(); iEnemy != mp_Enemies.cend() ; ++iEnemy)
    {
        Enemy *EnemyItem = (*iEnemy);
        if (EnemyItem->Update())
        {
            QPoint CurrentNextPoint = mapGlobalToTile(EnemyItem->getTargetPoint());
            QPointF NextTarget = mapTileToGlobal(mp_Graph.getNextPathPoint(CurrentNextPoint, mp_PathResult));
            EnemyItem->setTargetPos(NextTarget);
        }
    }
}

void GameScene::KillEnemy(Enemy *EnemyItem)
{
    removeItem(EnemyItem);
    mp_Enemies.remove(EnemyItem);
    mp_Level->AddCosts(EnemyItem->getBonus());
    delete EnemyItem;
    bool Won = false;

    if (mp_Level->KillEnemy())
        Won = mp_Level->NextLevel();

    emit LevelChanged(mp_Level);
    if (Won)
        emit GameWon();
}


