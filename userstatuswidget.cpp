#include "userstatuswidget.h"
#include "ui_userstatuswidget.h"

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

void UserStatusWidget::LevelChanged(QPointer<Level> CurrentLevel)
{
    if (!CurrentLevel)
        return;

    ui->m_CostValue->setText(QString::number(CurrentLevel->getCosts()));
    ui->m_LifeValue->setText(QString::number(CurrentLevel->getLifes()));
    ui->m_LevelValue->setText(QString::number(CurrentLevel->getLevelNumber()));
}

