#include <QtTest>

// add necessary includes here

#include "../src/model.h"

class fileTest : public QObject
{
    Q_OBJECT

public:
    fileTest();
    ~fileTest();

private slots:
    void test_case1();
    void test_case2();

};

fileTest::fileTest()
{

}

fileTest::~fileTest()
{

}

void fileTest::test_case1()
{
    Model& rM = Model::instance();
    rM.parse("file1.json");
    bool bOK;
    double dMedian = rM.median(bOK);
    QCOMPARE(bOK, true);
    QCOMPARE(dMedian, 4);
}

void fileTest::test_case2()
{
    Model& rM = Model::instance();
    rM.parse("file2.json");
    bool bOK;
    double dMedian = rM.median(bOK);
    QCOMPARE(bOK, true);
    QCOMPARE(dMedian, 4.5);
}

QTEST_APPLESS_MAIN(fileTest)

#include "tst_filetest.moc"
