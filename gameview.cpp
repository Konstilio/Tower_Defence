#include "gameview.h"
#include "gamescene.h"
#include "generalutils.h"
#include "gameviewstate.h"
#include "tower.h"
#include "level.h"

GameView::GameView(QWidget *Parent)
    : QGraphicsView(Parent)
    , mp_CurrentZoom(1.)
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
    setSceneRect(mp_Scene->sceneRect());

    QPixmap bcg(":/Images/sandbackground.jpg");
    setBackgroundBrush(bcg.scaled(width(), height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setCacheMode(CacheBackground);

    setMouseTracking(true);

    mp_NormalState = new NormalViewState(this, mp_Scene, this);
    mp_BuildState = new BuildViewState(this, mp_Scene, this);

    connect(this, &GameView::UpgradeWanted, mp_NormalState, &NormalViewState::UpgradeRequested);
    connect(this, &GameView::SellWanted, mp_NormalState, &NormalViewState::SellRequested);
    connect(mp_NormalState, &NormalViewState::TowerSelected, this, &GameView::TowerSelected);
    connect(mp_NormalState, &NormalViewState::SelectionCleared, this, &GameView::SelectionCleared);
    connect(mp_BuildState, &BuildViewState::wantLeave, this, &GameView::ChangeStateToNormal);
    connect(mp_Scene, &GameScene::SceneUpdated, mp_BuildState, &BuildViewState::onSceneUpdated);
    connect(mp_Scene, &GameScene::LevelChanged, this, &GameView::LevelChanged, Qt::QueuedConnection);
    mp_Scene->StartGame();

    mp_State = mp_NormalState;
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

void GameView::mousePressEvent(QMouseEvent *event)
{
    mp_State->mousePressEvent(event);
}

void GameView::wheelEvent(QWheelEvent *event)
{
//    constexpr double scaleFactor = 1.15;
//    if(event->delta() > 0)
//    {
//       auto nextZoom = mp_CurrentZoom * scaleFactor;
//       if (nextZoom > 2.)
//           return;

//       mp_CurrentZoom = nextZoom;
//       scale(scaleFactor, scaleFactor);
//    }
//    else
//    {
//       auto nextZoom = mp_CurrentZoom / scaleFactor;
//       if (nextZoom < 1.)
//           return;

//       mp_CurrentZoom = nextZoom;
//       scale(1.0 / scaleFactor, 1.0 / scaleFactor);
//    }
}

void GameView::BuildWanted(int towerId)
{
    mp_BuildState->AttachTower(TowerFactory::Create(towerId));
    ChangeState(mp_BuildState);
}

void GameView::ChangeState(GameViewState *State)
{
    mp_State->onExit();
    mp_State = State;
    mp_State->onEnter();
}

void GameView::ChangeStateToNormal()
{
    ChangeState(mp_NormalState);
}
