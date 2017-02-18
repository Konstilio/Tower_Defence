#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

class GameScene;
class GameViewState;
class NormalViewState;
class BuildViewState;
class Tower;
class Level;

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
    void BuildWanted(int towerId);

signals:
    void LevelChanged(Level *CurrentLevel);
    void UpgradeWanted();
    void TowerSelected();

private:
    void ChangeState(GameViewState *State);
    void ChangeStateToNormal();

    GameScene *mp_Scene;
    GameViewState *mp_State;

    double mp_CurrentZoom;

    NormalViewState *mp_NormalState = nullptr;
    BuildViewState *mp_BuildState = nullptr;
};

#endif // GAMEVIEW_H
