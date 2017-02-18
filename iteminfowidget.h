#ifndef ITEMINFOWIDGET_H
#define ITEMINFOWIDGET_H

#include <QWidget>
#include <QPointer>
#include "tower.h"
#include "enemy.h"

namespace Ui {
    class ItemInfoWidget;
}

class ItemInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemInfoWidget(QWidget *parent = 0);
    ~ItemInfoWidget();

public slots:
    void onTowerSelected(QPointer<Tower> TowerItem);
    void onEnemySelected(QPointer<Enemy> EnemyItem);
    void onSelectionCleared();

private:
    QString getEnemyHealthString(const QPointer<Enemy> &EnemyItem);
    QString getEnemySpeedString(const QPointer<Enemy> &EnemyItem);

    Ui::ItemInfoWidget *ui;
};

#endif // ITEMINFOWIDGET_H
