#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class GameView;
class UserStatusWidget;
class UserBuildMenuWidget;
class ItemInfoWidget;

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
    ItemInfoWidget *mp_ItemInfoWidget;

};

#endif // WIDGET_H
