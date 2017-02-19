#ifndef TILEGRAPH_H
#define TILEGRAPH_H

#include <QHash>
#include <QPoint>
#include <QSet>
#include <vector> // not QVector to support move

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

struct ShortestPathResult;

class TileGraph
{
public:
    TileGraph() = default;
    TileGraph(int TilesWidth, int TilesHeight);

    Tile &getTile(const QPoint &TilePos);
    const Tile &getTile(const QPoint & TilePos) const;
    Tile &getTile(int X, int Y);
    const Tile &getTile(int X, int Y) const;

    int static MaxTileDistance(const QPoint &LeftTile, const QPoint &RightTile);
    void getLogicNeighbours(const Tile &Current, int Distance, QSet<const Tile *> &o_Result) const; // 9 Neighbours (include itself, if distance 1)
    std::vector<const Tile *> getPathNeighbours(const Tile &Current) const; // 4 Neighbours

    int getTileIndex(const Tile *CurrentTile) const;
    int getSize() const;

    // Shortest Pathes
    ShortestPathResult getShortestPathToDestination(const QPoint &DestinationTilePos) const;
    QPoint getNextPathPoint(const QPoint &TilePos, ShortestPathResult const &Result) const;
    int getPathDistance(const QPoint &TilePos, ShortestPathResult const &Result) const;
    bool AllPathesExists(ShortestPathResult const &Result) const;
private:
    template<typename ShortestPathAlgorithm>
    ShortestPathResult getShortestPath(const QPoint &DestinationTilePos) const;
    static constexpr bool mpc_UseBFS = true;

    int mp_TilesWidth;
    int mp_TilesHeight;
    std::vector<Tile> mp_Tiles;
};

struct ShortestPathResult
{
    std::vector<int> m_Distance;
    std::vector<const Tile *> m_Next;
    const Tile *m_Destination = nullptr;
};

struct DijkstraSearch
{
    // Find shortest pathes to dst for all graph
    ShortestPathResult operator()(const TileGraph &Graph, const QPoint &TilePos);
    ShortestPathResult operator()(const TileGraph &Graph, int X, int Y);
};

struct BFSSearch
{
    // Find shortest pathes to dst for all graph
    ShortestPathResult operator()(const TileGraph &Graph, const QPoint &TilePos);
    ShortestPathResult operator()(const TileGraph &Graph, int X, int Y);
};

template<typename ShortestPathAlgorithm>
ShortestPathResult TileGraph::getShortestPath(const QPoint &DestinationTilePos) const
{
    return ShortestPathAlgorithm()(*this, DestinationTilePos);
}

#endif // TILEGRAPH_H
