import QtQuick 2.0

Item {
    id: id_root

    property int value: carData.gearValue

    FontLoader {
        id: font_gear_number
        source: "fonts/digital-7.ttf"
    }

    Rectangle {
        id: id_gear

        anchors.centerIn: parent
        height: Math.min(id_root.width, id_root.height)
        width: height
        radius: width/2
        color: "black"
        border.color: "light green"
        border.width: id_gear.height * 0.02

        Repeater {
            model: 7

            Item {
                height: id_gear.height/2
                transformOrigin: Item.Bottom
                rotation: index * 30 + 200
                x: id_gear.width/2

                Rectangle {
                    height: id_gear.height * 0.12 + index * id_gear.height * 0.01
                    width: height
                    color: index == value ? "white" : "black"
                    radius: width/2
                    antialiasing: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: id_gear.height * 0.05
                    border.width: 2
                    border.color: "white"

                    Text {
                        anchors.centerIn: parent
                        color: index == value ? "black" : "white"
                        text: index
                        font.pixelSize: parent.height * 0.5
                        font.family: font_gear_number.name
                    }
                }
            }
        }
    }

    Text {
        font.family: font_gear_number.name
        anchors.centerIn: parent
        text: "GEAR"
        color: "light green"
        font.pixelSize: id_gear.height * 0.8
    }
}
