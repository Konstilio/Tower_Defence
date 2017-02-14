#include "gameview.h"
#include "gamescene.h"
#include "generalutils.h"
#include "gameviewstate.h"
#include "tower.h"

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

    QPixmap bcg(":/Images/sandbackground.jpg");
    setBackgroundBrush(bcg.scaled(width(), height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setCacheMode(CacheBackground);

    setMouseTracking(true);

    mp_State = new NormalViewState(this, mp_Scene, this);
    connect(mp_State, &GameViewState::wantLeave, this, &GameView::changeStateToNormal);
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

void GameView::buildWanted(int towerId)
{
    changeState(new BuildViewState(this, mp_Scene, TowerFactory::Create(towerId), this));
}

void GameView::changeState(GameViewState *State)
{
    mp_State->onExit();
    mp_State->deleteLater();
    mp_State = State;
    connect(mp_State, &GameViewState::wantLeave, this, &GameView::changeStateToNormal);
    mp_State->onEnter();
}

void GameView::changeStateToNormal()
{
    changeState(new NormalViewState(this, mp_Scene, this));
}
