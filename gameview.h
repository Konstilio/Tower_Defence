#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

class GameScene;
class GameViewState;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *Parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

public slots:
    void buildWanted(int towerId);

private:
    void changeState(GameViewState *State);

    GameScene *mp_Scene;
    GameViewState *mp_State;
};

#endif // GAMEVIEW_H
