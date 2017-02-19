#include "tilegraph.h"
#include "qmath.h"
#include <QMap>
#include <utility>
#include <limits>
#include <set>
#include <QQueue>
#include <type_traits>

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
    mp_Tiles.reserve(mp_TilesWidth * mp_TilesHeight);
    for (int iHeight = 0; iHeight < TilesHeight; ++iHeight)
    {
        for (int iWidth = 0; iWidth < TilesWidth; ++iWidth)
            mp_Tiles.push_back(Tile(iWidth, iHeight));
    }
}

Tile &TileGraph::getTile(const QPoint &TilePos)
{
    return getTile(TilePos.x(), TilePos.y());
}

const Tile &TileGraph::getTile(const QPoint &TilePos) const
{
    return getTile(TilePos.x(), TilePos.y());
}

Tile &TileGraph::getTile(int X, int Y)
{
    return mp_Tiles[Y * mp_TilesWidth + X];
}

const Tile &TileGraph::getTile(int X, int Y) const
{
    return mp_Tiles[Y * mp_TilesWidth + X];
}

int TileGraph::MaxTileDistance(const QPoint &LeftTile, const QPoint &RightTile)
{
    return qMax(qAbs(LeftTile.x() - RightTile.x()), qAbs(LeftTile.y() - RightTile.y()));
}

std::vector<const Tile *> TileGraph::getPathNeighbours(const Tile &Current) const
{
    std::vector<const Tile *> Result;
    Result.reserve(4);
    if (Current.getY() > 0)
        Result.push_back(&getTile({Current.getX(), Current.getY() - 1}));
    if (Current.getX() > 0)
        Result.push_back(&getTile({Current.getX() - 1, Current.getY()}));
    if (Current.getY() < mp_TilesHeight - 1)
        Result.push_back(&getTile({Current.getX(), Current.getY() + 1}));
    if (Current.getX() < mp_TilesWidth - 1)
        Result.push_back(&getTile({Current.getX() + 1, Current.getY()}));

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

int TileGraph::getTileIndex(const Tile *CurrentTile) const
{
    return CurrentTile->getY() * mp_TilesWidth + CurrentTile->getX();
}

int TileGraph::getSize() const
{
    return mp_TilesWidth * mp_TilesHeight;
}

QPoint TileGraph::getNextPathPoint(const QPoint &TilePos, const ShortestPathResult &Result) const
{
    const auto &CurrentTile = getTile(TilePos);
    const Tile *NextTile = Result.m_Next[getTileIndex(&CurrentTile)];
    Q_ASSERT(NextTile);
    return {NextTile->getX(), NextTile->getY()};
}

int TileGraph::getPathDistance(const QPoint &TilePos, const ShortestPathResult &Result) const
{
    const auto &CurrentTile = getTile(TilePos);
    return Result.m_Distance[getTileIndex(&CurrentTile)];
}

bool TileGraph::AllPathesExists(const ShortestPathResult &Result) const
{
    for (auto const &TileItem : mp_Tiles)
    {
        if (TileItem.getType() != Tile::EType_Busy && TileItem.getType() != Tile::EType_Temp)
        {
            if (Result.m_Next[getTileIndex(&TileItem)] == nullptr)
                return false;
        }
    }
    return true;
}

ShortestPathResult TileGraph::getShortestPathToDestination(const QPoint &DestinationTilePos) const
{
    return getShortestPath<std::conditional<mpc_UseBFS, BFSSearch, DijkstraSearch>::type>(DestinationTilePos);
}

// DijkstraSearch

ShortestPathResult DijkstraSearch::operator()(const TileGraph &Graph, int X, int Y)
{
    std::set<std::pair<int ,const Tile *>> DistanceMap; // std here to use ordered set
    const Tile *Destination = &Graph.getTile(X, Y);
    DistanceMap.emplace(std::make_pair(0, Destination));
    
    ShortestPathResult Result;
    Result.m_Distance = std::vector<int>(Graph.getSize(), std::numeric_limits<int>::max());
    Result.m_Next = std::vector<const Tile *>(Graph.getSize(), nullptr);

    Result.m_Distance[Graph.getTileIndex(Destination)] = 0;
    Result.m_Next[Graph.getTileIndex(Destination)] = Destination;
    Result.m_Destination = Destination;
    
    // Run Dijkstra loop
    while (!DistanceMap.empty())
    {
        auto it = DistanceMap.begin();
        int СurrentDistance = it->first;
        const Tile *CurrentTile = it->second;
        DistanceMap.erase(it);

        auto Neighbours = Graph.getPathNeighbours(*CurrentTile);
        for (const Tile * Neighbour : Neighbours)
        {
            if (Neighbour->getType() == Tile::EType_Busy || Neighbour->getType() == Tile::EType_Temp)
                continue;

            int NewDistance = СurrentDistance + 1;
            int OldDistance = Result.m_Distance[Graph.getTileIndex(Neighbour)];
            if (NewDistance < OldDistance)
            {
                DistanceMap.erase(std::make_pair(OldDistance, Neighbour));
                Result.m_Distance[Graph.getTileIndex(Neighbour)] = NewDistance;
                Result.m_Next[Graph.getTileIndex(Neighbour)] = CurrentTile;
                DistanceMap.emplace(std::make_pair(NewDistance, Neighbour));
            }
        }
    }

    return Result;
}

ShortestPathResult DijkstraSearch::operator()(const TileGraph &Graph, const QPoint &TilePos)
{
    return operator ()(Graph, TilePos.x(), TilePos.y());
}

ShortestPathResult BFSSearch::operator()(const TileGraph &Graph, int X, int Y)
{
    const Tile *Destination = &Graph.getTile(X, Y);
    QQueue<const Tile *> Queue;
    Queue.enqueue(Destination);

    ShortestPathResult Result;
    Result.m_Distance = std::vector<int>(Graph.getSize(), std::numeric_limits<int>::max());
    Result.m_Next = std::vector<const Tile *>(Graph.getSize(), nullptr);

    Result.m_Distance[Graph.getTileIndex(Destination)] = 0;
    Result.m_Next[Graph.getTileIndex(Destination)] = Destination;
    Result.m_Destination = Destination;

    while (!Queue.empty())
    {
        const Tile *CurrentTile = Queue.dequeue();
        int СurrentDistance = Result.m_Distance[Graph.getTileIndex(CurrentTile)];
        auto Neighbours = Graph.getPathNeighbours(*CurrentTile);
        for (const Tile *Neighbour : Neighbours)
        {
            if (Neighbour->getType() == Tile::EType_Busy || Neighbour->getType() == Tile::EType_Temp)
                continue;

            int NewDistance = СurrentDistance + 1;
            int OldDistance = Result.m_Distance[Graph.getTileIndex(Neighbour)];
            if (NewDistance < OldDistance)
            {
                Result.m_Distance[Graph.getTileIndex(Neighbour)] = NewDistance;
                Result.m_Next[Graph.getTileIndex(Neighbour)] = CurrentTile;
                Queue.enqueue(Neighbour);
            }

        }
    }

    return Result;

}

ShortestPathResult BFSSearch::operator()(const TileGraph &Graph, const QPoint &TilePos)
{
    return operator ()(Graph, TilePos.x(), TilePos.y());
}

