#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gameview.h"
#include "userstatuswidget.h"
#include "userbuildmenuwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    GameView *mp_View;
    UserStatusWidget *mp_StatusWidget;
    UserBuildMenuWidget *mp_BuildMenuWidget;

};

#endif // WIDGET_H
