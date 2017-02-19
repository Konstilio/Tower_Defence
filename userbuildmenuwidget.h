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
    void onGameResumed();
    void onGamePaused();

    void onTowerSelected(bool CanBeUpgraded);
    void onSelectionCleared();

signals:
    void BuildWanted(int towerId);
    void UpgradeWanted();
    void SellWanted();

private:
    Ui::UserBuildMenuWidget *ui;
    QButtonGroup *mp_ButtonGroup;

private slots:
    void onButtonClicked(int buttonId);

};

#endif // USERBUILDMENUWIDGET_H
