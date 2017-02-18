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
    ui->mp_UpgradeTowerButton->setIcon(QIcon(":/Images/upgrade.png"));
    //ui->mp_RemoveTowerButton->setIcon(QIcon(":/Images/tree.png"));

    mp_ButtonGroup = new QButtonGroup(this);
    mp_ButtonGroup->addButton(ui->mp_TreeTowerButton, Tower::ETowerId_Tree);
    mp_ButtonGroup->addButton(ui->mp_AcidTowerButton, Tower::ETowerId_Acid);
    mp_ButtonGroup->addButton(ui->mp_IceTowerButton, Tower::ETowerId_Ice);
    mp_ButtonGroup->addButton(ui->mp_StoneTowerButton, Tower::ETowerId_Stone);
    mp_ButtonGroup->addButton(ui->mp_UpgradeTowerButton, Tower::ETowerId_Upgrade);

    ui->mp_UpgradeTowerButton->hide();

    connect(mp_ButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

}

UserBuildMenuWidget::~UserBuildMenuWidget()
{
    delete ui;
}

void UserBuildMenuWidget::onTowerSelected()
{
    ui->mp_UpgradeTowerButton->show();
}

void UserBuildMenuWidget::onButtonClicked(int buttonId)
{
   if (buttonId == Tower::ETowerId_Upgrade)
       emit UpgradeWanted();
   else
       emit BuildWanted(buttonId);
}
