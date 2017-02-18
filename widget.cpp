#include "widget.h"
#include "ui_widget.h"
#include "level.h"

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

    Layout->addWidget(mp_View, 0, 0, 10, 5);
    Layout->addWidget(mp_StatusWidget, 0, 5);
    Layout->addWidget(mp_BuildMenuWidget, 1, 5, 2, 1);

    Layout->setSpacing(3);
    setLayout(Layout);

    resize(Layout->sizeHint());

    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::BuildWanted, mp_View, &GameView::BuildWanted, Qt::QueuedConnection);
    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::UpgradeWanted, mp_View, &GameView::UpgradeWanted, Qt::QueuedConnection);
    connect(mp_BuildMenuWidget, &UserBuildMenuWidget::SellWanted, mp_View, &GameView::SellWanted, Qt::QueuedConnection);
    connect(mp_View, &GameView::LevelChanged, mp_StatusWidget, &UserStatusWidget::LevelChanged);
    connect(mp_View, &GameView::TowerSelected, mp_BuildMenuWidget, &UserBuildMenuWidget::onTowerSelected);
    connect(mp_View, &GameView::SelectionCleared, mp_BuildMenuWidget, &UserBuildMenuWidget::onSelectionCleared);
}

Widget::~Widget()
{
    delete ui;
}
