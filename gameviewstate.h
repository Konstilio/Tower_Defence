#ifndef GAMEVIEWSTATE_H
#define GAMEVIEWSTATE_H

#include <QObject>
#include <QMouseEvent>
class GameView;
class GameScene;
class Tower;

class GameViewState : public QObject
{
    Q_OBJECT
public:
    GameViewState(GameView *View, GameScene *Scene, QObject *Parent = 0);

    void virtual mouseMoveEvent(QMouseEvent *event) = 0;
    void virtual leaveEvent() = 0;
    void virtual onEnter() = 0;
    void virtual onExit() = 0;

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

    void onEnter() override;
    void onExit() override;
};

class BuildViewState : public GameViewState
{
    Q_OBJECT
public:
    BuildViewState(GameView *View, GameScene *Scene, Tower *TowerToBuild, QObject *Parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent() override;

    void onEnter() override;
    void onExit() override;

    Tower *mp_Tower;
};

#endif // GAMEVIEWSTATE_H
