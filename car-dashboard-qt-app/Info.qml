import QtQuick 2.0

Item {
    id: id_root

    property var currentDate: new Date()
    property int value: carData.fuelValue
    property int fuel_value_change: carData.fuelValue

    function getCurrentDate() {
        var currentDate = new Date();
        var day = currentDate.getDate();
        var monthNames = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
        var month = monthNames[currentDate.getMonth()]; // Get month name
        var year = currentDate.getFullYear();
        return month + " " + day + " " + year;
    }


    Timer {
        id: timer
        repeat: true
        interval: 1000
        running: true
        onTriggered: id_root.currentDate = new Date()
    }

    Rectangle {
        id: id_info

        anchors.centerIn: parent
        height: Math.min(id_root.width, id_root.height)
        width: height
        radius: width/2
        color: "black"
        border.color: "light green"
        border.width: id_info.height * 0.02

        FontLoader {
            id: font_for_day_time
            source: "fonts/digital-7.ttf"
        }

        //Display current date
        Text {
            id: id_date
            anchors {
                horizontalCenter: id_info.horizontalCenter
                top: id_info.top
                topMargin: id_info.height * 0.07
            }
            color: "red"
            font.pixelSize: id_info.height * 0.07
            font.family: font_for_day_time.name
            text: getCurrentDate()  // Call the updated function
        }


        // display current time
        Text {
            id: id_clock
            anchors {
                horizontalCenter: id_info.horizontalCenter
                top: id_date.bottom
                topMargin: id_info.height * 0.01
            }
            color: "#00ffff"
            font.pixelSize: id_info.height * 0.1
            font.family: font_for_day_time.name
            text: carData.currentTime
        }

        // display Fuel change
        Fuel {
            x: id_info.height * 0.3
            y: id_info.height * 0.35
            width: id_info.height * 0.55
            height: width
            z: 1
            value: id_root.value
        }
    }
}
