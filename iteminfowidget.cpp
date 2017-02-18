#include "iteminfowidget.h"
#include "ui_iteminfowidget.h"

ItemInfoWidget::ItemInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemInfoWidget)
{
    ui->setupUi(this);
    onSelectionCleared();
}

ItemInfoWidget::~ItemInfoWidget()
{
    delete ui;
}

void ItemInfoWidget::onTowerSelected(QPointer<Tower> TowerItem)
{
    ui->m_EnemyWidget->hide();
    if (!TowerItem)
    {
        ui->m_TowerWidget->hide();
        return;
    }

    ui->m_CostTowerValue->setText(QString::number(TowerItem->getCost()));
    ui->m_PowerTowerValue->setText(QString::number(TowerItem->getPower()));
    ui->m_RangeTowerValue->setText(QString::number(TowerItem->getPower()));
    ui->m_UpgradeCostTowerValue->setText(QString::number(TowerItem->getUpgradeCost()));
    ui->m_SellCostTowerValue->setText(QString::number(TowerItem->getSellCost()));

    ui->m_TowerWidget->show();
}

void ItemInfoWidget::onEnemySelected(QPointer<Enemy> EnemyItem)
{
    ui->m_TowerWidget->hide();
    if (!EnemyItem)
    {
        ui->m_EnemyWidget->hide();
        return;
    }

    ui->m_BonusEnemyValue->setText(QString::number(EnemyItem->getBonus()));
    ui->m_SpeedEnemyValue->setText(getEnemySpeedString(EnemyItem));
    ui->m_HealthEnemyValue->setText(getEnemyHealthString(EnemyItem));
    ui->m_EnemyWidget->show();
}

void ItemInfoWidget::onSelectionCleared()
{
    ui->m_TowerWidget->hide();
    ui->m_EnemyWidget->hide();
}

QString ItemInfoWidget::getEnemyHealthString(const QPointer<Enemy> &EnemyItem)
{
    return QString("%1 / %2")
            .arg(QString::number(EnemyItem->getHealth()))
            .arg(QString::number(EnemyItem->getInitialHealth()))
    ;
}

QString ItemInfoWidget::getEnemySpeedString(const QPointer<Enemy> &EnemyItem)
{
    switch (EnemyItem->getSpeed())
    {
    case Enemy::ESpeed_Slow:
        return "slow";
    case Enemy::ESpeed_Medium:
        return "medium";
    case Enemy::ESpeed_Fast:
        return "fast";
    }
}
