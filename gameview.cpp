#include "gameview.h"
#include "gamescene.h"
#include "generalutils.h"

GameView::GameView(QWidget *Parent)
    : QGraphicsView(Parent)
{
    auto const &Utils = GeneralUtils::Instance();

    setFixedSize(Utils.GameViewSize());
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    mp_Scene = new GameScene
            (
                Utils.GameViewSize().width()
                , Utils.GameViewSize().height()
                , Utils.TileSize()
                , this
            );

    this->setScene(mp_Scene);
}
