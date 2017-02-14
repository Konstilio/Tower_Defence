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

void NormalViewState::onEnter()
{

}

void NormalViewState::onExit()
{

}

BuildViewState::BuildViewState(GameView *View, GameScene *Scene, Tower *TowerToBuild, QObject *Parent)
    : GameViewState(View, Scene, Parent)
    , mp_Tower(TowerToBuild)
{

}

void BuildViewState::mouseMoveEvent(QMouseEvent *event)
{
    mp_Scene->removeItem(mp_Tower);
    mp_Scene->addGameItem(mp_Tower, mp_Scene->mapGlobalToTile(event->pos()));
}

void BuildViewState::leaveEvent()
{
    mp_Scene->removeItem(mp_Tower);
}

void BuildViewState::onEnter()
{
    mp_View->setCursor(Qt::PointingHandCursor);
}

void BuildViewState::onExit()
{
    mp_View->setCursor(Qt::ArrowCursor);
}
