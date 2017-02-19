#include "widget.h"
#include "ui_widget.h"
#include "gameview.h"
#include "userstatuswidget.h"
#include "userbuildmenuwidget.h"
#include "iteminfowidget.h"
#include "level.h"
#include "gamestatewidget.h"

#include <QGridLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QGridLayout *Layout = new QGridLayout();
    mp_View = new GameView(this);
    mp_StatusWidget = new UserStatusWidget(this);
    mp_BuildMenuWidget = new UserBuildMenuWidget(this);
    mp_ItemInfoWidget = new ItemInfoWidget(this);
    mp_GameStateWidget = new GameStateWidget(this);

    Layout->addWidget(mp_View, 0, 0, 12, 5);
    Layout->addWidget(mp_StatusWidget, 0, 5, 3, 1);
    Layout->addWidget(mp_BuildMenuWidget, 3, 5, 2, 1);
    Layout->addWidget(mp_ItemInfoWidget, 5, 5, 5, 1);
    Layout->addWidget(mp_GameStateWidget, 10, 5, 2, 1);

    Layout->setSpacing(3);
    setLayout(Layout);

    resize(Layout->sizeHint());

    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::BuildWanted, mp_View, &GameView::BuildWanted, Qt::QueuedConnection);
    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::UpgradeWanted, mp_View, &GameView::UpgradeWanted, Qt::QueuedConnection);
    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::SellWanted, mp_View, &GameView::SellWanted, Qt::QueuedConnection);
    connect(mp_View, &GameView::LevelChanged, mp_StatusWidget, &UserStatusWidget::LevelChanged);
    connect(mp_View, SIGNAL(TowerSelected(bool)), mp_BuildMenuWidget, SLOT(onTowerSelected(bool)));
    connect(mp_View, &GameView::SelectionCleared, mp_BuildMenuWidget, &UserBuildMenuWidget::onSelectionCleared);
    connect(mp_View, &GameView::GameResumed, mp_BuildMenuWidget, &UserBuildMenuWidget::onGameResumed);
    connect(mp_View, &GameView::GamePaused, mp_BuildMenuWidget, &UserBuildMenuWidget::onGamePaused);
    connect(mp_View, SIGNAL(TowerSelected(QPointer<Tower>)), mp_ItemInfoWidget, SLOT(onTowerSelected(QPointer<Tower>)));
    connect(mp_View, &GameView::EnemySelected, mp_ItemInfoWidget, &ItemInfoWidget::onEnemySelected);
    connect(mp_View, &GameView::SelectionCleared, mp_ItemInfoWidget, &ItemInfoWidget::onSelectionCleared);
    connect(mp_View, &GameView::TowerAttached, mp_ItemInfoWidget, &ItemInfoWidget::onTowerSelected);
    connect(mp_View, &GameView::AttachedTowerCleared, mp_ItemInfoWidget, &ItemInfoWidget::onSelectionCleared);
    connect(mp_GameStateWidget, &GameStateWidget::StartRequested, mp_View, &GameView::Start, Qt::QueuedConnection);
    connect(mp_GameStateWidget, &GameStateWidget::PauseRequested, mp_View, &GameView::Pause, Qt::QueuedConnection);
    connect(mp_GameStateWidget, &GameStateWidget::ResumeRequested, mp_View, &GameView::Resume, Qt::QueuedConnection);
    connect(mp_View, &GameView::GameWon, mp_GameStateWidget, &GameStateWidget::onGameEnded);
    connect(mp_View, &GameView::GameLost, mp_GameStateWidget, &GameStateWidget::onGameEnded);
}

Widget::~Widget()
{
    delete ui;
}
