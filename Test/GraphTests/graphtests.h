#ifndef GRAPHTESTS_H
#define GRAPHTESTS_H

#include <QObject>
#include <QtTest/QtTest>

class GraphTests : public QObject
{
    Q_OBJECT
private slots:
    void TestPath();
};

#endif // GRAPHTESTS_H
