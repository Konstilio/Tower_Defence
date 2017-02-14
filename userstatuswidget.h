#ifndef USERSTATUSWIDGET_H
#define USERSTATUSWIDGET_H

#include <QWidget>
class Tower;

namespace Ui {
class UserStatusWidget;
}

class UserStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserStatusWidget(QWidget *parent = 0);
    ~UserStatusWidget();

public slots:
     void onTowerBuilt(int TowerCost);

private:
    Ui::UserStatusWidget *ui;
};

#endif // USERSTATUSWIDGET_H
