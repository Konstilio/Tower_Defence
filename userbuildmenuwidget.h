#ifndef USERBUILDMENUWIDGET_H
#define USERBUILDMENUWIDGET_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class UserBuildMenuWidget;
}

class UserBuildMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserBuildMenuWidget(QWidget *parent = 0);
    ~UserBuildMenuWidget();

public slots:
    void onTowerSelected();

signals:
    void BuildWanted(int towerId);
    void UpgradeWanted();

private:
    Ui::UserBuildMenuWidget *ui;
    QButtonGroup *mp_ButtonGroup;

private slots:
    void onButtonClicked(int buttonId);

};

#endif // USERBUILDMENUWIDGET_H
