import QtQuick 2.0
import QtTest 1.2

TestCase {
    name: "CarDashboardTest"

    Item {
        id: testRoot
        width: 400
        height: 400

        Component {
            id: dashboardComponent
            Info {
                id: dashboard
            }
        }

        function test_getCurrentDate() {
            var expectedFormat = /^\w+ \d+ \d{4}$/; // Example: "Jan 1 2024"
            var currentDateString = dashboard.getCurrentDate();
            compare(expectedFormat.test(currentDateString), true, "The date format should be 'Month Day Year'");
        }
    }
}
