#ifndef USERSTATUSWIDGET_H
#define USERSTATUSWIDGET_H

#include <QWidget>
#include <QPointer>
#include "level.h"

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
    void LevelChanged(QPointer<Level> CurrentLevel);

private:
    Ui::UserStatusWidget *ui;
};

#endif // USERSTATUSWIDGET_H
