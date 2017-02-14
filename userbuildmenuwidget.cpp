#include "userbuildmenuwidget.h"
#include "ui_userbuildmenuwidget.h"
#include "tower.h"
#include <QDebug>

UserBuildMenuWidget::UserBuildMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserBuildMenuWidget)
{
    ui->setupUi(this);

    ui->mp_TreeTowerButton->setIcon(QIcon(":/Images/tree.png"));
    ui->mp_RedTowerButton2->setIcon(QIcon(":/Images/icetower.png"));
    ui->mp_RedTowerButton3->setIcon(QIcon(":/Images/stonetower.png"));
    ui->mp_RedTowerButton4->setIcon(QIcon(":/Images/tree.png"));
    ui->mp_RedTowerButton5->setIcon(QIcon(":/Images/tree.png"));
    ui->mp_RedTowerButton6->setIcon(QIcon(":/Images/tree.png"));

    mp_ButtonGroup = new QButtonGroup(this);
    mp_ButtonGroup->addButton(ui->mp_TreeTowerButton, TreeTower::getId());

    connect(mp_ButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

}

UserBuildMenuWidget::~UserBuildMenuWidget()
{
    delete ui;
}

void UserBuildMenuWidget::onButtonClicked(int buttonId)
{
    qDebug() << "here";
    emit buildWanted(buttonId);
}
