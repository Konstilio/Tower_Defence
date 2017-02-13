#include "userbuildmenuwidget.h"
#include "ui_userbuildmenuwidget.h"

UserBuildMenuWidget::UserBuildMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserBuildMenuWidget)
{
    ui->setupUi(this);

    ui->mp_RedTowerButton->setIcon(QIcon(":/Images/RedTower.png"));
    ui->mp_RedTowerButton2->setIcon(QIcon(":/Images/RedTower.png"));
    ui->mp_RedTowerButton3->setIcon(QIcon(":/Images/RedTower.png"));
    ui->mp_RedTowerButton4->setIcon(QIcon(":/Images/RedTower.png"));
    ui->mp_RedTowerButton5->setIcon(QIcon(":/Images/RedTower.png"));
    ui->mp_RedTowerButton6->setIcon(QIcon(":/Images/RedTower.png"));

}

UserBuildMenuWidget::~UserBuildMenuWidget()
{
    delete ui;
}
