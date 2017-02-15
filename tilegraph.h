#ifndef TILEGRAPH_H
#define TILEGRAPH_H

#include <QHash>
#include <QPoint>
#include <QVector>
#include <QSet>

inline uint qHash (const QPoint & key)
{
    return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
}

class Tile
{
public :
    enum EType
    {
        EType_Empty = 0
        , EType_Busy = 1
        , EType_Temp = 2
        , EType_Start = 3
        , EType_End = 4
    };

    Tile (int X, int Y);
    Tile (const QPoint &Point);

    void setType(EType Type);
    EType getType() const;
    int getX() const;
    int getY() const;

private:
    int mp_X;
    int mp_Y;
    EType mp_Type;
};

class TileGraph
{
public:
    TileGraph(int TilesWidth, int TilesHeight);

    Tile &getTile(const QPoint &TilePos);
    const Tile &getTile(const QPoint & TilePos) const;

    int static MaxTileDistance(const QPoint &LeftTile, const QPoint &RightTile);
    void getLogicNeighbours(const Tile& Current, int Distance, QSet<const Tile *> &o_Result) const; // 9 Neighbours (include itself, if distance 1)
private:
    QVector<const Tile *> getPathNeighbours(const Tile& Current) const; // 4 Neighbours

    int mp_TilesWidth;
    int mp_TilesHeight;
    QHash<QPoint, Tile *> mp_Tiles;
};

#endif // TILEGRAPH_H
