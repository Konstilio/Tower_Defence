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
    ui->mp_AcidTowerButton->setIcon(QIcon(":/Images/acidtower.png"));
    ui->mp_IceTowerButton->setIcon(QIcon(":/Images/icetower.png"));
    ui->mp_StoneTowerButton->setIcon(QIcon(":/Images/stonetower.png"));
    //ui->mp_UpgradeTowerButton->setIcon(QIcon(":/Images/tree.png"));
    //ui->mp_RemoveTowerButton->setIcon(QIcon(":/Images/tree.png"));

    mp_ButtonGroup = new QButtonGroup(this);
    mp_ButtonGroup->addButton(ui->mp_TreeTowerButton, TreeTower::getId());
    mp_ButtonGroup->addButton(ui->mp_AcidTowerButton, AcidTower::getId());
    mp_ButtonGroup->addButton(ui->mp_IceTowerButton, IceTower::getId());
    mp_ButtonGroup->addButton(ui->mp_StoneTowerButton, StoneTower::getId());

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
