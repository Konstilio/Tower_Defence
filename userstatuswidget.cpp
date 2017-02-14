#include "userstatuswidget.h"
#include "ui_userstatuswidget.h"
#include "tower.h"

UserStatusWidget::UserStatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserStatusWidget)
{
    ui->setupUi(this);
}

UserStatusWidget::~UserStatusWidget()
{
    delete ui;
}

void UserStatusWidget::onTowerBuilt(int TowerCost)
{

}
