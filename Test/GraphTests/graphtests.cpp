#include "graphtests.h"
#include "../../tilegraph.h"

void GraphTests::TestBase()
{
    TileGraph Graph(5, 5);
    QCOMPARE(Graph.getSize(), 25);

    const Tile& T1 = Graph.getTile(0, 1);
    QCOMPARE(Graph.getTileIndex(&T1), 5);

    const Tile& T2 = Graph.getTile(1, 0);
    QCOMPARE(Graph.getTileIndex(&T2), 1);

    const Tile& T3 = Graph.getTile(4, 4);
    QCOMPARE(Graph.getTileIndex(&T3), 24);
}

void GraphTests::TestClearPath()
{
    TileGraph Graph(5, 5);
    ShortestPathResult Result = DijkstraSearch()(Graph, 4, 4);

    const Tile& T1 = Graph.getTile(4, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T1)], 0);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T1)], &T1);

    const Tile& T2 = Graph.getTile(4, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T2)], 1);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T2)], &T1);

    const Tile& T3 = Graph.getTile(3, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T3)], 1);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T3)], &T1);

    const Tile& T4 = Graph.getTile(3, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T4)], 2);

    const Tile& T5 = Graph.getTile(0, 0);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T5)], 8);
}

void GraphTests::TestBusyPath()
{
    TileGraph Graph(5, 5);
    Graph.getTile(4, 3).setType(Tile::EType_Busy);
    Graph.getTile(3, 4).setType(Tile::EType_Busy);
    ShortestPathResult Result = DijkstraSearch()(Graph, 4, 4);

    const Tile& T1 = Graph.getTile(4, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T1)], 0);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T1)], &T1);

    const Tile& T2 = Graph.getTile(4, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T2)], std::numeric_limits<int>::max());
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T2)], static_cast<const Tile *>(nullptr));

    const Tile& T3 = Graph.getTile(3, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T3)], std::numeric_limits<int>::max());
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T3)], static_cast<const Tile *>(nullptr));

    const Tile& T4 = Graph.getTile(3, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T4)], std::numeric_limits<int>::max());

    const Tile& T5 = Graph.getTile(0, 0);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T5)], std::numeric_limits<int>::max());
}

void GraphTests::TestHalfBusyPath()
{
    TileGraph Graph(5, 5);
    Graph.getTile(4, 0).setType(Tile::EType_Busy);
    Graph.getTile(3, 1).setType(Tile::EType_Busy);
    Graph.getTile(2, 2).setType(Tile::EType_Busy);
    Graph.getTile(1, 3).setType(Tile::EType_Busy);
    Graph.getTile(0, 4).setType(Tile::EType_Busy);
    ShortestPathResult Result = DijkstraSearch()(Graph, 4, 4);

    const Tile& T1 = Graph.getTile(4, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T1)], 0);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T1)], &T1);

    const Tile& T2 = Graph.getTile(4, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T2)], 1);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T2)], &T1);

    const Tile& T3 = Graph.getTile(3, 4);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T3)], 1);
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T3)], &T1);

    const Tile& T4 = Graph.getTile(3, 3);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T4)], 2);

    const Tile& T5 = Graph.getTile(0, 0);
    QCOMPARE(Result.m_Distance[Graph.getTileIndex(&T5)], std::numeric_limits<int>::max());
    QCOMPARE(Result.m_Next[Graph.getTileIndex(&T5)], static_cast<const Tile *>(nullptr));
}

