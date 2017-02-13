#ifndef USERSTATUSWIDGET_H
#define USERSTATUSWIDGET_H

#include <QWidget>

namespace Ui {
class UserStatusWidget;
}

class UserStatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserStatusWidget(QWidget *parent = 0);
    ~UserStatusWidget();

private:
    Ui::UserStatusWidget *ui;
};

#endif // USERSTATUSWIDGET_H
