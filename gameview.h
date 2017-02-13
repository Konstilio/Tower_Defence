#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

class GameScene;

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView();

private:
    GameScene *mp_Scene;

    constexpr static int mcp_Width = 1200;
    constexpr static int mcp_Height = 900;
};

#endif // GAMEVIEW_H
