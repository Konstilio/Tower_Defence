#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

class GameScene;
class GameViewState;
class Tower;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *Parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public slots:
    void buildWanted(int towerId);

signals:
    void towerBuilt(int TowerCost);

private:
    void changeState(GameViewState *State);
    void changeStateToNormal();

    GameScene *mp_Scene;
    GameViewState *mp_State;

    double mp_CurrentZoom;
};

#endif // GAMEVIEW_H
