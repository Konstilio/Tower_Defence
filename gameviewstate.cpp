#include "gameviewstate.h"
#include "gameview.h"
#include "gamescene.h"
#include "tower.h"
#include <QCursor>

GameViewState::GameViewState(GameView *View, GameScene *Scene, QObject *Parent)
    : QObject(Parent)
    , mp_View(View)
    , mp_Scene(Scene)
{

}

// NormalViewState

NormalViewState::NormalViewState(GameView *View, GameScene *Scene, QObject *Parent)
    : GameViewState(View, Scene, Parent)
{

}

void NormalViewState::mouseMoveEvent(QMouseEvent *event)
{

}

void NormalViewState::leaveEvent()
{

}

void NormalViewState::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        ClearSelectedTower();
        return;
    }

    if (event->button() != Qt::LeftButton)
        return;

    ClearSelectedTower();

    auto Items = mp_Scene->items(event->pos());
    for (auto *Item : Items)
    {
        auto *TowerItem = qgraphicsitem_cast<Tower *>(Item);
        if (TowerItem != nullptr)
        {
            mp_SelectedTower = TowerItem;
            mp_SelectedTower->Indicate(Tower::EIndicator_Select);

            return;
        }
    }
}

void NormalViewState::onEnter()
{

}

void NormalViewState::onExit()
{

}

void NormalViewState::ClearSelectedTower()
{
    if (mp_SelectedTower)
    {
        mp_SelectedTower->ClearIndicator();
        mp_SelectedTower = nullptr;
    }
}

// BuildViewState

BuildViewState::BuildViewState(GameView *View, GameScene *Scene, Tower *TowerToBuild, QObject *Parent)
    : GameViewState(View, Scene, Parent)
    , mp_Tower(TowerToBuild)
{

}

void BuildViewState::mouseMoveEvent(QMouseEvent *event)
{
    mp_Scene->removeItem(mp_Tower);
    mp_Scene->AddTempGameItem(mp_Tower, mp_Scene->mapGlobalToTile(event->pos()));
}

void BuildViewState::leaveEvent()
{
    mp_Scene->removeItem(mp_Tower);
}

void BuildViewState::mousePressEvent(QMouseEvent *event)
{
    mp_Build = event->button() == Qt::LeftButton;
    emit wantLeave();
}

void BuildViewState::onEnter()
{
    mp_Scene->AddMesh();
    mp_Tower->Indicate(Tower::EIndicator_CanBuild);
    mp_View->setCursor(Qt::PointingHandCursor);
}

void BuildViewState::onExit()
{
    if (!mp_Build)
        mp_Scene->removeItem(mp_Tower);
    else
    {
        mp_Scene->CacheTower(mp_Tower);
        emit mp_View->towerBuilt(mp_Tower->getCost());
        mp_Tower->ClearIndicator();
    }

    mp_Scene->RemoveMesh();
    mp_View->setCursor(Qt::ArrowCursor);
}
