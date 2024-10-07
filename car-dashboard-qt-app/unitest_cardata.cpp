// #include <QtTest/QtTest>
// #include "CarData.h"

// // Create a test class that inherits from QObject
// class TestCarData : public QObject
// {
//     Q_OBJECT

// private slots:
//     // Initialize and cleanup functions (optional)
//     void initTestCase();    // Called before the first test
//     void cleanupTestCase(); // Called after the last test
//     void init();            // Called before each test
//     void cleanup();         // Called after each test

//     // Actual unit tests
//     void testInitialValues();
//     void testSetSpeedValue();
//     void testSetGearValue();
//     void testFetchDataFromAPI();
// };

// // Define the init and cleanup methods
// void TestCarData::initTestCase()
// {
//     // Code to initialize before all tests (e.g., setup resources)
//     qDebug() << "Starting test suite...";
// }

// void TestCarData::cleanupTestCase()
// {
//     // Code to clean up after all tests are run
//     qDebug() << "Finished test suite.";
// }

// void TestCarData::init()
// {
//     // Code to run before each test (e.g., reset object state)
//     qDebug() << "Starting a new test case...";
// }

// void TestCarData::cleanup()
// {
//     // Code to run after each test (e.g., clean up)
//     qDebug() << "Test case finished.";
// }

// // Unit test for initial values
// void TestCarData::testInitialValues()
// {
//     CarData carData;
//     QCOMPARE(carData.speedValue(), 0);       // Ensure speedValue is initially 0
//     QCOMPARE(carData.gearValue(), 0);        // Ensure gearValue is initially 0
//     QCOMPARE(carData.fuelValue(), 0);        // Ensure fuelValue is initially 0
//     QCOMPARE(carData.temperatureValue(), 0); // Ensure temperatureValue is initially 0
// }

// // Unit test for setting speed value
// void TestCarData::testSetSpeedValue()
// {
//     CarData carData;
//     carData.setSpeedValue(100);
//     QCOMPARE(carData.speedValue(), 100); // Ensure speedValue is set correctly
// }

// // Unit test for setting gear value
// void TestCarData::testSetGearValue()
// {
//     CarData carData;
//     carData.setGearValue(3);
//     QCOMPARE(carData.gearValue(), 3); // Ensure gearValue is set correctly
// }

// // Unit test for fetching data from API (Mocked)
// void TestCarData::testFetchDataFromAPI()
// {
//     // Mocking network requests would be needed for this test.
//     // You can use Qt's QSignalSpy or a mock QNetworkAccessManager for this.
//     qDebug() << "Mocking network request to test API.";
// }

// // Run the test suite
// QTEST_MAIN(TestCarData)
// #include "unitest_cardata.moc"
