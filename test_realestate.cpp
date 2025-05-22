#include <QtTest/QtTest>
#include "realestate.h"

class TestRealEstate : public QObject {
    Q_OBJECT

private slots:
    void testValidParse();
    void testInvalidParse();
};

void TestRealEstate::testValidParse() {
    RealEstate estate;
    std::string line = "\"Иванов И.И.\" 2022.05.15 4500000 \"ул. Ленина, 1\" 3";
    estate.parse(line);
    QCOMPARE(estate.owner, std::string("Иванов И.И."));
    QCOMPARE(estate.registrationDate.tm_year, 2022 - 1900);
    QCOMPARE(estate.registrationDate.tm_mon, 4); // май
    QCOMPARE(estate.registrationDate.tm_mday, 15);
    QCOMPARE(estate.estimatedCost, 4500000);
    QCOMPARE(estate.address, std::string("ул. Ленина, 1"));
    QCOMPARE(estate.numberOfRooms, 3);
}

void TestRealEstate::testInvalidParse() {
    RealEstate estate;
    std::string invalid = "неправильная строка";
    QVERIFY_EXCEPTION_THROWN(estate.parse(invalid), std::invalid_argument);
}

QTEST_MAIN(TestRealEstate)
#include "test_realestate.moc"
