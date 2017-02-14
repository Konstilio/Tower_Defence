#include "gameview.h"
#include "gamescene.h"
#include "generalutils.h"
#include "gameviewstate.h"
#include "tower.h"

GameView::GameView(QWidget *Parent)
    : QGraphicsView(Parent)
{
    auto const &Utils = GeneralUtils::Instance();

    setFixedSize(Utils.GameViewSize());
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    mp_Scene = new GameScene
            (
                Utils.GameViewSize().width()
                , Utils.GameViewSize().height()
                , Utils.TileSize()
                , this
            );

    this->setScene(mp_Scene);

    setMouseTracking(true);
    mp_State = new NormalViewState(this, mp_Scene, this);
    mp_State->onEnter();
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    mp_State->mouseMoveEvent(event);
}

void GameView::leaveEvent(QEvent *event)
{
    mp_State->leaveEvent();
}

void GameView::buildWanted(int towerId)
{
    changeState(new BuildViewState(this, mp_Scene, TowerFactory::Create(towerId), this));
}

void GameView::changeState(GameViewState *State)
{
    mp_State->onExit();
    mp_State->deleteLater();
    mp_State = State;
    mp_State->onEnter();
}
