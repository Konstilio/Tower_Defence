#ifndef GAMEVIEWSTATE_H
#define GAMEVIEWSTATE_H

#include <QObject>
#include <QMouseEvent>
#include <QPointer>
#include "tower.h"
class GameView;
class GameScene;

class GameViewState : public QObject
{
    Q_OBJECT
public:
    GameViewState(GameView *View, GameScene *Scene, QObject *Parent = 0);
    void SetScene(GameScene *Scene);
    
    void virtual mouseMoveEvent(QMouseEvent *event) = 0;
    void virtual leaveEvent() = 0;
    void virtual mousePressEvent(QMouseEvent *event) = 0;

    void virtual onEnter() = 0;
    void virtual onExit() = 0;

    void virtual onSceneUpdated() = 0;

protected:
    GameView *mp_View;
    GameScene *mp_Scene;
};

class NormalViewState : public GameViewState
{
    Q_OBJECT
public:
    NormalViewState(GameView *View, GameScene *Scene, QObject *Parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent() override;
    void mousePressEvent(QMouseEvent *event) override;

    void onEnter() override;
    void onExit() override;

    void onSceneUpdated() override;
public slots:
    void UpgradeRequested();
    void SellRequested();
    void onLevelChanged();


signals:
    void TowerSelected(bool);
    void TowerSelected(QPointer<Tower>);
    void EnemySelected(QPointer<Enemy>);
    void SelectionCleared();

private:
    void ClearSelected();

    QPointer<Tower> mp_SelectedTower;
    QPointer<Enemy> mp_SelectedEnemy;
};

class BuildViewState : public GameViewState
{
    Q_OBJECT
public:
    BuildViewState(GameView *View, GameScene *Scene, QObject *Parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent() override;
    void mousePressEvent(QMouseEvent *event) override;

    void onEnter() override;
    void onExit() override;

    void AttachTower(Tower *TowerItem);
    void onSceneUpdated() override;
signals:
    void WantLeave();
    void TowerAttached(QPointer<Tower> TowerItem);
    void AttachedTowerCleared();

private:
    Tower *mp_Tower = nullptr;
    bool mp_WantBuild = false;
    bool mp_CanBuild = false;

    QPoint mp_PrevTilePos;
};

#endif // GAMEVIEWSTATE_H
