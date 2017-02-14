#include "gamescene.h"
#include <QDebug>
#include "tower.h"
#include "ammo.h"
#include <QTimer>

GameScene::GameScene(int Width, int Height, int TileSize, QObject *Parent)
    : QGraphicsScene(Parent)
    , mp_TileSize(TileSize)
    , mp_Width(Width)
    , mp_Height(Height)
{
    setSceneRect(0, 0, Width, Height);
    InitUpdateTimer();
}

QPoint GameScene::mapGlobalToTile(QPoint GloalPos)
{
    return QPoint( GloalPos.x() / mp_TileSize, GloalPos.y() / mp_TileSize);
}

QPoint GameScene::mapTileToGlobal(QPoint TilePos)
{
    return QPoint( TilePos.x() * mp_TileSize, TilePos.y() * mp_TileSize);
}

void GameScene::AddTempGameItem(QGraphicsItem *Item, QPoint TilePos)
{
    addItem(Item);
    QPoint GlobalPos = mapTileToGlobal(TilePos);
    Item->setX(GlobalPos.x());
    Item->setY(GlobalPos.y());
}

void GameScene::AddMesh()
{
    auto MeshWidth = mp_Width / mp_TileSize;
    auto MeshHeight = mp_Height / mp_TileSize;

    for (int yMesh = 0; yMesh < MeshHeight; ++yMesh)
    {
        for (int xMesh = 0; xMesh < MeshWidth; ++xMesh)
        {
            qDebug() << xMesh * mp_TileSize << ' ' << yMesh * mp_TileSize;
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , (xMesh + 1) * mp_TileSize, yMesh * mp_TileSize, QPen(QColor(255, 0, 0, 100))));
            mp_MeshLines.append(addLine(xMesh * mp_TileSize, yMesh * mp_TileSize , xMesh * mp_TileSize, (yMesh + 1) * mp_TileSize, QPen(QColor(255, 0, 0, 100))));
        }
    }
}

void GameScene::RemoveMesh()
{
    while (!mp_MeshLines.empty())
    {
        removeItem(mp_MeshLines.first());
        mp_MeshLines.pop_front();
    }
}

void GameScene::CacheTower(Tower *TowerItem)
{
    qDebug() << "CacheTower: " << TowerItem;
    mp_Towers.insert(TowerItem);
}

void GameScene::Update()
{
    for (auto iTower = mp_Towers.cbegin(); iTower != mp_Towers.cend(); ++iTower)
        TowerShoot(*iTower);
}

void GameScene::InitUpdateTimer()
{
    mp_UpdateTimer = new QTimer(this);
    connect(mp_UpdateTimer, &QTimer::timeout, this, &GameScene::Update);
    mp_UpdateTimer->start(25);
}

void GameScene::TowerShoot(Tower *TowerItem)
{
    qDebug() << "TowerShoot: " << TowerItem;
    Ammo *AmmoItem = new Ammo(TowerItem);
    addItem(AmmoItem);
    AmmoItem->setX(TowerItem->center().x());
    AmmoItem->setY(TowerItem->center().y());
}

