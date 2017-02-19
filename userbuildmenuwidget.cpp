#include "userbuildmenuwidget.h"
#include "ui_userbuildmenuwidget.h"
#include "tower.h"
#include <QDebug>

UserBuildMenuWidget::UserBuildMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserBuildMenuWidget)
{
    ui->setupUi(this);

    ui->mp_TreeTowerButton->setIcon(QIcon(":/Images/treetower50.png"));
    ui->mp_AcidTowerButton->setIcon(QIcon(":/Images/acidtower50.png"));
    ui->mp_IceTowerButton->setIcon(QIcon(":/Images/icetower50.png"));
    ui->mp_StoneTowerButton->setIcon(QIcon(":/Images/stonetower50.png"));
    ui->mp_UpgradeTowerButton->setIcon(QIcon(":/Images/upgrade.png"));
    ui->mp_SellTowerButton->setIcon(QIcon(":/Images/sell40.png"));

    mp_ButtonGroup = new QButtonGroup(this);
    mp_ButtonGroup->addButton(ui->mp_TreeTowerButton, Tower::ETowerId_Tree);
    mp_ButtonGroup->addButton(ui->mp_AcidTowerButton, Tower::ETowerId_Acid);
    mp_ButtonGroup->addButton(ui->mp_IceTowerButton, Tower::ETowerId_Ice);
    mp_ButtonGroup->addButton(ui->mp_StoneTowerButton, Tower::ETowerId_Stone);
    mp_ButtonGroup->addButton(ui->mp_UpgradeTowerButton, Tower::ETowerId_Upgrade);
    mp_ButtonGroup->addButton(ui->mp_SellTowerButton, Tower::ETowerId_Sell);

    onSelectionCleared();
    onGamePaused();

    connect(mp_ButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

}

UserBuildMenuWidget::~UserBuildMenuWidget()
{
    delete ui;
}

void UserBuildMenuWidget::onGameResumed()
{
    for (auto *Button : mp_ButtonGroup->buttons())
        Button->setEnabled(true);

    ui->mp_UpgradeTowerButton->setDisabled(true);
    ui->mp_SellTowerButton->setDisabled(true);
}

void UserBuildMenuWidget::onGamePaused()
{
    for (auto *Button : mp_ButtonGroup->buttons())
        Button->setDisabled(true);
}

void UserBuildMenuWidget::onTowerSelected(bool CanBeUpgraded)
{
    ui->mp_UpgradeTowerButton->show();
    ui->mp_UpgradeTowerButton->setEnabled(CanBeUpgraded);
    ui->mp_SellTowerButton->setEnabled(true);
}

void UserBuildMenuWidget::onSelectionCleared()
{
    ui->mp_UpgradeTowerButton->setDisabled(true);
    ui->mp_SellTowerButton->setDisabled(true);
}

void UserBuildMenuWidget::onButtonClicked(int buttonId)
{
   if (buttonId == Tower::ETowerId_Upgrade)
       emit UpgradeWanted();
   else if (buttonId == Tower::ETowerId_Sell)
       emit SellWanted();
   else
       emit BuildWanted(buttonId);
}
