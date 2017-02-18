#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QPointer>

class GameScene;
class GameViewState;
class NormalViewState;
class BuildViewState;
class Tower;
class Level;
class Enemy;

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
    void onSceneUpdated();
    
    void Start();
    void Pause();
    void Resume();

signals:
    void TowerSelected(bool);
    void TowerSelected(QPointer<Tower>);
    void EnemySelected(QPointer<Enemy>);
    void TowerAttached(QPointer<Tower>);
    void AttachedTowerCleared();

    void SelectionCleared();
    void LevelChanged(QPointer<Level> CurrentLevel);
    void UpgradeWanted();
    void SellWanted();

private:
    void ChangeState(GameViewState *State);
    void ChangeStateToNormal();

    GameScene *mp_Scene = nullptr;
    GameViewState *mp_State = nullptr;

    double mp_CurrentZoom;

    NormalViewState *mp_NormalState = nullptr;
    BuildViewState *mp_BuildState = nullptr;
};

#endif // GAMEVIEW_H
