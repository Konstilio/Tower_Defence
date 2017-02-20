#include "gameview.h"
#include "gamescene.h"
#include "generalutils.h"
#include "gameviewstate.h"
#include "tower.h"
#include "enemy.h"
#include "level.h"
#include "resultinfodialog.h"

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

    connect(this, &GameView::UpgradeWanted, mp_NormalState, &NormalViewState::UpgradeRequested, Qt::QueuedConnection);
    connect(this, &GameView::SellWanted, mp_NormalState, &NormalViewState::SellRequested, Qt::QueuedConnection);
    connect(this, &GameView::LevelChanged, mp_NormalState, &NormalViewState::onLevelChanged, Qt::QueuedConnection);
    connect(mp_NormalState, SIGNAL(TowerSelected(bool)), this, SIGNAL(TowerSelected(bool)));
    connect(mp_NormalState, SIGNAL(TowerSelected(QPointer<Tower>)), this, SIGNAL(TowerSelected(QPointer<Tower>)));
    connect(mp_NormalState, &NormalViewState::EnemySelected, this, &GameView::EnemySelected);
    connect(mp_NormalState, &NormalViewState::SelectionCleared, this, &GameView::SelectionCleared);
    connect(mp_BuildState, &BuildViewState::WantLeave, this, &GameView::ChangeStateToNormal);
    connect(mp_BuildState, &BuildViewState::TowerAttached, this, &GameView::TowerAttached);
    connect(mp_BuildState, &BuildViewState::AttachedTowerCleared, this, &GameView::AttachedTowerCleared);
    connect(mp_Scene, &GameScene::SceneUpdated, this, &GameView::onSceneUpdated);
    connect(mp_Scene, &GameScene::LevelChanged, this, &GameView::LevelChanged, Qt::QueuedConnection);
    connect(mp_Scene, &GameScene::GameLost, this, &GameView::onGameLostLogic, Qt::QueuedConnection);
    connect(mp_Scene, &GameScene::GameWon, this, &GameView::onGameWonLogic, Qt::QueuedConnection);
}

void GameView::Start()
{
    if (mp_State)
        mp_State->onExit();
    setEnabled(true);

    mp_Scene->StartGame();
    mp_State = mp_NormalState;
    mp_State->onEnter();

    emit GameResumed();
}

void GameView::Pause()
{
    if (mp_State)
        mp_State->onExit();

    setDisabled(true);
    mp_Scene->PauseGame();

    emit GamePaused();
}

void GameView::Resume()
{
    setEnabled(true);
    mp_State = mp_NormalState;
    mp_State->onEnter();
    mp_Scene->ResumeGame();

    emit GameResumed();
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    if (mp_State)
        mp_State->mouseMoveEvent(event);
}

void GameView::leaveEvent(QEvent *event)
{
    (void)event;
    if (mp_State)
        mp_State->leaveEvent();
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (mp_State)
        mp_State->mousePressEvent(event);
}


void GameView::BuildWanted(int towerId)
{
    mp_BuildState->AttachTower(TowerFactory::Create(towerId));
    ChangeState(mp_BuildState);
}

void GameView::onSceneUpdated()
{
    if (mp_State)
        mp_State->onSceneUpdated();
}

void GameView::onGameWonLogic()
{
    Pause();
    emit GameWon();

    ResultInfoDialog *Dialog = new ResultInfoDialog(ResultInfoDialog::EStyle_Won, this);
    Dialog->setModal(true);
    Dialog->show();
}

void GameView::onGameLostLogic()
{
    Pause();
    emit GameLost();

    ResultInfoDialog *Dialog = new ResultInfoDialog(ResultInfoDialog::EStyle_Lost, this);
    Dialog->setModal(true);
    Dialog->show();
}

void GameView::ChangeState(GameViewState *State)
{
    if (mp_State == State)
        return;

    if (mp_State)
        mp_State->onExit();
    mp_State = State;
    mp_State->onEnter();
}

void GameView::ChangeStateToNormal()
{
    ChangeState(mp_NormalState);
}
