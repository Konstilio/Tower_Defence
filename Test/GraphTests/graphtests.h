#ifndef GRAPHTESTS_H
#define GRAPHTESTS_H

#include <QObject>
#include <QtTest/QtTest>

class GraphTests : public QObject
{
    Q_OBJECT
private slots:
    void TestBase();
    void TestClearPath();
    void TestBusyPath();
    void TestHalfBusyPath();
};

#endif // GRAPHTESTS_H
