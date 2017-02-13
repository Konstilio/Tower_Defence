#include "gameview.h"
#include "gamescene.h"

GameView::GameView()
{
    setFixedSize(mcp_Width, mcp_Height);
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    mp_Scene = new GameScene(mcp_Width, mcp_Height, 40, 30, this);
    mp_Scene->setBackgroundBrush(Qt::black);
    this->setScene(mp_Scene);
}
