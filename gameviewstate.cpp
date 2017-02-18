#include "gameviewstate.h"
#include "gameview.h"
#include "gamescene.h"
#include "tower.h"
#include <QCursor>
#include <QDebug>

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
            emit TowerSelected(mp_SelectedTower->CanBeUpgraded());

            return;
        }
    }

    emit SelectionCleared();
}

void NormalViewState::onEnter()
{

}

void NormalViewState::onExit()
{
    ClearSelectedTower();
}

void NormalViewState::UpgradeRequested()
{
    if (!mp_SelectedTower)
        return;

    mp_Scene->UpgradeTower(mp_SelectedTower);
}

void NormalViewState::SellRequested()
{
    if (!mp_SelectedTower)
        return;

    mp_Scene->SellTower(mp_SelectedTower);
    ClearSelectedTower();
}

void NormalViewState::ClearSelectedTower()
{
    if (mp_SelectedTower)
    {
        mp_SelectedTower->ClearIndicator();
        mp_SelectedTower.clear();
    }
}

// BuildViewState

BuildViewState::BuildViewState(GameView *View, GameScene *Scene, QObject *Parent)
    : GameViewState(View, Scene, Parent)
    , mp_PrevTilePos({-1,-1})
{

}

void BuildViewState::mouseMoveEvent(QMouseEvent *event)
{
    QPoint CurrentTilePos = mp_Scene->mapGlobalToTile(event->pos());
    if (mp_PrevTilePos == CurrentTilePos)
        return;

    mp_Scene->RemoveTempItem(mp_Tower);
    mp_Scene->AddTempGameItem(mp_Tower, CurrentTilePos);
    mp_CanBuild = mp_Scene->CanBuildTower(mp_Tower);
    mp_Tower->Indicate(mp_CanBuild ? Tower::EIndicator_CanBuild : Tower::EIndicator_CanNotBuild);
    mp_PrevTilePos = CurrentTilePos;
}

void BuildViewState::leaveEvent()
{
    mp_Scene->RemoveTempItem(mp_Tower);
}

void BuildViewState::mousePressEvent(QMouseEvent *event)
{
    mp_WantBuild = event->button() == Qt::LeftButton;
    if ((mp_WantBuild && mp_CanBuild) || !mp_WantBuild)
        emit wantLeave();
}

void BuildViewState::onEnter()
{
    mp_Tower->Indicate(Tower::EIndicator_CanBuild);
    mp_View->setCursor(Qt::PointingHandCursor);
}

void BuildViewState::onExit()
{
    if (!mp_WantBuild)
        mp_Scene->RemoveTempItem(mp_Tower);
    else
    {
        mp_Scene->BuildTower(mp_Tower);
        mp_Tower->ClearIndicator();
    }

    mp_Tower = nullptr;
    mp_View->setCursor(Qt::ArrowCursor);
    mp_PrevTilePos = {-1, -1};
}

void BuildViewState::AttachTower(Tower *Tower)
{
    mp_Tower = Tower;
}

void BuildViewState::onSceneUpdated()
{
    if (!mp_Tower)
        return;

    mp_CanBuild = mp_Scene->CanBuildTower(mp_Tower);
    mp_Tower->Indicate(mp_CanBuild ? Tower::EIndicator_CanBuild : Tower::EIndicator_CanNotBuild);
}
