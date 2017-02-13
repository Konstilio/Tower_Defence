#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

class GameScene;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *Parent = 0);

private:
    GameScene *mp_Scene;

};

#endif // GAMEVIEW_H
