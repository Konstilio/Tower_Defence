#ifndef GAMESTATEWIDGET_H
#define GAMESTATEWIDGET_H

#include <QWidget>

namespace Ui {
class GameStateWidget;
}

class GameStateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameStateWidget(QWidget *parent = 0);
    ~GameStateWidget();

signals:
    void StartRequested();
    void PauseRequested();
    void ResumeRequested();
    
    
private:
    void onStartClicked();
    void onPauseClicked();
    
    Ui::GameStateWidget *ui;
    bool mp_Paused = false;
};

#endif // GAMESTATEWIDGET_H
