#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
public:
    GameScene(int Width, int Height, int MeshWidth, int MeshHeight, QObject *Parent = Q_NULLPTR);
};

#endif // GAMESCENE_H
