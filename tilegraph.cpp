#include "tilegraph.h"
#include "qmath.h"
#include <QMap>
#include <utility>
#include <limits>
#include <set>

// Tile
Tile::Tile(int X, int Y)
    : mp_X(X)
    , mp_Y(Y)
    , mp_Type(EType_Empty)
{

}

Tile::Tile(const QPoint &Point)
    : mp_X(Point.x())
    , mp_Y(Point.y())
    , mp_Type(EType_Empty)
{

}

void Tile::setType(Tile::EType Type)
{
    mp_Type = Type;
}

Tile::EType Tile::getType() const
{
    return mp_Type;
}

int Tile::getX() const
{
    return mp_X;
}

int Tile::getY() const
{
    return mp_Y;
}

// TileGraph
TileGraph::TileGraph(int TilesWidth, int TilesHeight)
    : mp_TilesWidth(TilesWidth)
    , mp_TilesHeight(TilesHeight)
{
    for (int iWidth = 0; iWidth < TilesWidth; ++iWidth)
    {
        for (int iHeight = 0; iHeight < TilesHeight; ++iHeight)
            mp_Tiles.insert(QPoint(iWidth, iHeight), new Tile(iWidth, iHeight));
    }
}

Tile &TileGraph::getTile(const QPoint &TilePos)
{
    return *mp_Tiles[TilePos];
}

const Tile &TileGraph::getTile(const QPoint &TilePos) const
{
    return *mp_Tiles[TilePos];
}

int TileGraph::MaxTileDistance(const QPoint &LeftTile, const QPoint &RightTile)
{
    return qMax(qAbs(LeftTile.x() - RightTile.x()), qAbs(LeftTile.y() - RightTile.y()));
}

QVector<const Tile *> TileGraph::getPathNeighbours(const Tile &Current) const
{
    QVector<const Tile *> Result;
    Result.reserve(4);
    if (Current.getX() > 0)
        Result.push_back(&getTile({Current.getX() - 1, Current.getY()}));
    if (Current.getY() > 0)
        Result.push_back(&getTile({Current.getX(), Current.getY() - 1}));
    if (Current.getX() < mp_TilesWidth - 1)
        Result.push_back(&getTile({Current.getX() + 1, Current.getY()}));
    if (Current.getY() < mp_TilesHeight - 1)
        Result.push_back(&getTile({Current.getX(), Current.getY() + 1}));

    return Result;
}

void TileGraph::getLogicNeighbours(const Tile &Current, int Distance, QSet<const Tile *> &o_Result) const
{
    if (Distance == 0)
        return;

    for (int iX = -1; iX <=1; ++iX)
    {
        for (int iY = -1; iY <=1; ++iY)
        {
            if ((Current.getX() +iX >= 0) && (Current.getX() +iX < mp_TilesWidth) && (Current.getY() + iY >= 0) && (Current.getY() + iY < mp_TilesHeight))
            {
                const Tile &ThisTile = getTile({Current.getX() + iX, Current.getY() + iY});
                o_Result.insert(&ThisTile);
                getLogicNeighbours(ThisTile, Distance - 1, o_Result);
            }

        }
    }
}

void TileGraph::ForEachTile(std::function<void (const Tile *)> &&TileFunc) const
{
    for (auto iTile = mp_Tiles.begin(); iTile != mp_Tiles.end(); ++iTile)
        TileFunc(iTile.value());
}

// DijkstraSearch

DijkstraSearchResult DijkstraSearch::operator()(const TileGraph &Graph, const QPoint &TilePos)
{
    std::set<std::pair<int ,const Tile *>> DistanceMap; // std here to use ordered set
    const Tile *Destination = &Graph.getTile(TilePos);
    DistanceMap.emplace(std::make_pair(0, Destination));
    
    DijkstraSearchResult Result;
    Result.m_Distance[Destination] = 0;
    Result.m_Next[Destination] = nullptr;
    Result.m_Destination = Destination;
    
    // Init start data
    Graph.ForEachTile
    (
        [&](const Tile *CurrentTile)
        {
            if (CurrentTile != Destination)
            {
                DistanceMap.emplace(std::make_pair(std::numeric_limits<int>::max(), CurrentTile));
                Result.m_Distance[CurrentTile] = std::numeric_limits<int>::max();
                Result.m_Next[Destination] = nullptr;
            }
        }
    );
    
    // Run Dijkstra loop
    while (!DistanceMap.empty())
    {
        auto it = DistanceMap.begin();
        int СurrentDistance = it->first;
        const Tile *CurrentTile = it->second;
        DistanceMap.erase(it);

        QVector<const Tile *> Neighbours = Graph.getPathNeighbours(*CurrentTile);
        for (const Tile * Neighbour : Neighbours)
        {
            int NewDistance = СurrentDistance + 1;
            int OldDistance = Result.m_Distance[Neighbour];
            if (NewDistance < OldDistance)
            {
                DistanceMap.erase(std::make_pair(OldDistance, Neighbour));
                Result.m_Distance[Neighbour] = NewDistance;
                Result.m_Next[Neighbour] = CurrentTile;
                DistanceMap.emplace(std::make_pair(NewDistance, Neighbour));
            }
        }
    }

    return Result;
}
