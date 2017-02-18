#include "gameviewstate.h"
#include "gameview.h"
#include "gamescene.h"
#include "tower.h"
#include "enemy.h"
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
        ClearSelected();
        emit SelectionCleared();
        return;
    }

    if (event->button() != Qt::LeftButton)
        return;

    ClearSelected();

    auto Items = mp_Scene->items(event->pos());
    for (auto *Item : Items)
    {
        auto *TowerItem = qgraphicsitem_cast<Tower *>(Item);
        if (TowerItem)
        {
            mp_SelectedTower = TowerItem;
            mp_SelectedTower->Indicate(Tower::EIndicator_Select);
            emit TowerSelected(mp_Scene->CanUpgradeTower(mp_SelectedTower));
            emit TowerSelected(mp_SelectedTower);

            return;
        }

        auto *EnemyItem = qgraphicsitem_cast<Enemy *>(Item);
        if (EnemyItem)
        {
            mp_SelectedEnemy = EnemyItem;
            emit EnemySelected(mp_SelectedEnemy);
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
    ClearSelected();
    emit SelectionCleared();
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
    ClearSelected();
    emit SelectionCleared();
}

void NormalViewState::onLevelChanged()
{
    if (mp_SelectedTower)
        emit TowerSelected(mp_Scene->CanUpgradeTower(mp_SelectedTower));
}

void NormalViewState::onSceneUpdated()
{
    if (!mp_SelectedTower)
        emit EnemySelected(mp_SelectedEnemy);
}

void NormalViewState::ClearSelected()
{
    if (mp_SelectedTower)
    {
        mp_SelectedTower->ClearIndicator();
        mp_SelectedTower.clear();
    }

    mp_SelectedEnemy.clear();
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

    Q_ASSERT(mp_Tower);
    if (mp_Tower->scene() != mp_Scene)
    {
        mp_Scene->RemoveTempItem(mp_Tower);
        mp_Scene->AddTempGameItem(mp_Tower, CurrentTilePos);
    }
    else
        mp_Scene->MoveTempItem(mp_Tower, CurrentTilePos);

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
    if (mp_WantBuild)
        mp_CanBuild = mp_Scene->CanBuildTower(mp_Tower);
    if ((mp_WantBuild && mp_CanBuild) || !mp_WantBuild)
        emit WantLeave();
}

void BuildViewState::onEnter()
{
    mp_Tower->Indicate(Tower::EIndicator_CanBuild);
    mp_View->setCursor(Qt::PointingHandCursor);
    emit TowerAttached(mp_Tower);
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

    emit AttachedTowerCleared();
    mp_Tower = nullptr;
    mp_View->setCursor(Qt::ArrowCursor);
    mp_PrevTilePos = {-1, -1};
}

void BuildViewState::AttachTower(Tower *TowerItem)
{
    mp_Tower = TowerItem;
}

void BuildViewState::onSceneUpdated()
{
    if (!mp_Tower)
        return;

    mp_CanBuild = mp_Scene->CanBuildTower(mp_Tower);
    mp_Tower->Indicate(mp_CanBuild ? Tower::EIndicator_CanBuild : Tower::EIndicator_CanNotBuild);
}
