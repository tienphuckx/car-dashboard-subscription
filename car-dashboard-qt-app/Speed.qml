import QtQuick 2.0

Item {
    id: id_root
    property int value: 0

    Rectangle {
        id: id_speed

        property int numberIndexs: 15
        property int startAngle: 234
        property int angleLength: 18
        property int maxSpeed: 280

        anchors.centerIn: parent
        height: Math.min(id_root.width, id_root.height)
        width: height
        radius: width/2
        color: "black"
        border.color: "light green"
        border.width: id_speed.height * 0.02

        Canvas {
            id:canvas
            anchors.fill: parent
            contextType: "2d"
            rotation: 145
            antialiasing: true

            onPaint: {
                var context = canvas.getContext('2d');
                context.strokeStyle = "blue";
                context.lineWidth = id_speed.height * 0.05 / 2;
                context.beginPath();
                context.arc(id_speed.height / 2, id_speed.height / 2, id_speed.height / 2 - id_speed.height * 0.05, 0, Math.PI * 1.1, false);
                context.stroke();

                context.strokeStyle = "red";
                context.lineWidth = id_speed.height * 0.05 / 2;
                context.beginPath();
                context.arc(id_speed.height / 2, id_speed.height / 2, id_speed.height / 2 - id_speed.height * 0.05, Math.PI * 1.1, Math.PI * 1.4, false);
                context.stroke();
            }
        }

        Repeater {
            model: id_speed.numberIndexs

            Item {
                height: id_speed.height/2
                transformOrigin: Item.Bottom
                rotation: index * id_speed.angleLength + id_speed.startAngle
                x: id_speed.width/2

                // speed pointer for each number
                Rectangle {
                    height: id_speed.height * 0.05
                    width: height / 2
                    color: "light green"
                    antialiasing: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: id_speed.height * 0.03
                }

                // speed numbers
                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    x: 0
                    y: id_speed.height * 0.09
                    color: "light green"
                    rotation: 360 - (index * id_speed.angleLength + id_speed.startAngle)
                    text: index * (id_speed.maxSpeed / (id_speed.numberIndexs - 1))
                    font.pixelSize: id_speed.height * 0.05
                    font.family: "Comic Sans MS"
                }
            }
        }
    }

    // Speed -> dot at center
    Rectangle {
        id: id_center

        anchors.centerIn: parent
        height: id_speed.height*0.1
        width: height
        radius: width/2
        color: "light green"
    }

    FontLoader {
        id: font_for_km
        source: "fonts/digital-7.ttf"
    }

    // KM/H
    Text {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: id_speed.verticalCenter
            topMargin: id_speed.height * 0.1
        }
        text: "Km/h"
        color: "light green"
        font.pixelSize: id_speed.height * 0.1
        font.family: font_for_km.name
    }

    SpeedNeedle {
        id: id_speedNeedle
        anchors {
            top: id_speed.top
            bottom: id_speed.bottom
            horizontalCenter: parent.horizontalCenter
        }
        value: carData.speedValue
        startAngle: id_speed.startAngle
        angleLength: id_speed.angleLength / (id_speed.maxSpeed / (id_speed.numberIndexs - 1))
    }

    //Display temperature
    Rectangle {
        id: id_temper_left
        anchors.top: parent.bottom
        anchors.right: parent.horizontalCenter
        anchors.topMargin: -100
        anchors.rightMargin: 30  // Increase space from the right (parent center)
        height: id_speed.height * 0.55
        width: height
        radius: width / 2
        color: "light green"
        border.color: "black"
        border.width: 4  // Make the border thicker
        z: -1


        FontLoader {
            id: font_for_temp
            source: "fonts/digital-7.ttf"
        }

        Text {
            font.family: font_for_temp.name
            text: carData.temperatureValue
            font.pixelSize: 33
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 8
            color: "green"
        }

        Text {
            font.family: font_for_temp.name
            text: "~TEMPERATURE"
            font.pixelSize: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter  // Positioned below the number
            anchors.topMargin: 28  // Adjust margin to place it under the number
            color: "black"
        }

        //cang tay trai
        Rectangle {
            id: left_arm
            width: id_temper_left.width * 0.05
            height: id_temper_left.width * 0.5
            anchors.topMargin: -50 // ?
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -40
            color: "light green"
            anchors.top: id_temper_left.bottom
            z: -2

            // Rotate 25 degrees to the right
            rotation: 25
            transformOrigin: Item.Center  // Rotate around the center of the rectangle

        }
    }

    // for display humidity
    Rectangle {
        id: id_temper_right
        anchors.top: parent.bottom
        anchors.left: parent.horizontalCenter
        anchors.topMargin: -100
        anchors.leftMargin: 30  // Increase space from the left (parent center)
        height: id_speed.height * 0.55
        width: height
        radius: width / 2
        color: "light green"
        border.color: "black"
        border.width: 4  // Make the border thicker
        z: -1

        FontLoader {
            id: font_for_humidity
            source: "fonts/digital-7.ttf"
        }

        Text {
            font.family: font_for_humidity.name
            text: carData.humidity
            font.pixelSize: 33
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 8
            color: "green"

        }

        Text {
            font.family: font_for_temp.name
            text: "~HUMIDITY"
            font.pixelSize: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter  // Positioned below the number
            anchors.topMargin: 28  // Adjust margin to place it under the number
            color: "black"
        }

        //cang tay phai
        Rectangle {
            id: right_arm
            width: id_temper_right.width * 0.05
            height: id_temper_right.width * 0.5
            anchors.topMargin: -50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 40
            color: "light green"
            anchors.top: id_temper_right.bottom
            z: -2

            //Rotate 25 degrees to the right
            rotation: -25
            transformOrigin: Item.Center  // Rotate around the center of the rectangle

        }
    }


    //display GPS
    Rectangle {
        id: id_speed_bot
        anchors.top: parent.bottom
        anchors.topMargin: -100
        anchors.horizontalCenter: parent.horizontalCenter
        height: id_speed.height * 0.8
        width: height
        border.width: 4
        border.color: "light green"
        radius: width/2
        z: -2
        color: "black"

        Text {
            id: gps_value
            font.family: font_for_humidity.name
            text: carData.gps
            font.pixelSize: 23
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 38 // center --> offset to change possition
            color: "red"

        }

        Text {
            font.family: font_for_temp.name
            text: "GPS"
            font.pixelSize: 10
            anchors.horizontalCenter: parent.horizontalCenter
            // anchors.verticalCenterOffset: 58
            anchors.top: gps_value.bottom
            anchors.topMargin: 10  // Adjust margin to place it under the number
            color: "red"
        }


        // Dui left
        Rectangle {
            id: bottom_left
            anchors.top: id_speed_bot.bottom
            width: id_speed_bot.width * 0.3
            height: width
            anchors.right: id_speed_bot.horizontalCenter  // Align to the left of center
            anchors.rightMargin: id_speed_bot.width * 0.2
            anchors.topMargin: -65
            z: -3
            radius: width/2
            border.width: 2
            border.color: "light green"
            color: "black"

            Rectangle {
                id: id_foot_left
                anchors.top: parent.bottom
                width: bottom_left.width * 0.2
                height: bottom_left.height * 0.7
                border.color: "light green"
                color: "light green"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -15  // Move the rectangle 10 units to the left
                anchors.topMargin: -10
                z: -4

                Canvas {
                    id: id_final_feet_left
                    width: parent.width * 3
                    height: parent.height * 0.3  // Use only 30% of the parent's height at the bottom
                    anchors.bottom: parent.bottom  // Anchor to the bottom of the parent
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -parent.width
                    z: -5

                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.clearRect(0, 0, width, height); // Clear the canvas

                        // Set triangle color
                        ctx.fillStyle = "light green";

                        // Start drawing the right triangle pointing to the left
                        ctx.beginPath();
                        ctx.moveTo(width, height);      // Bottom-right corner
                        ctx.lineTo(0, height);          // Bottom-left corner
                        ctx.lineTo(width, 0);           // Top-right corner (apex pointing left)
                        ctx.closePath();

                        // Fill the triangle
                        ctx.fill();
                    }
                }

            }

        }

        // Dui right
        Rectangle {
            id: bottom_right
            anchors.top: id_speed_bot.bottom
            width: id_speed_bot.width * 0.3
            height: width
            anchors.left: id_speed_bot.horizontalCenter  // Align to the right of center
            anchors.leftMargin: id_speed_bot.width * 0.2 // add leftMargin to move to right
            anchors.topMargin: -65
            z: -3
            radius: width/2
            border.width: 2
            border.color: "light green"
            color: "black"

            Rectangle {
                id: id_foot_right
                anchors.top: parent.bottom
                width: bottom_left.width * 0.2
                height: bottom_left.height * 0.7
                border.color: "light green"
                color: "light green"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 15  // Move the rectangle 10 units to the left
                anchors.topMargin: -10
                z: -4

                //final foot
                Canvas {
                    id: id_final_feet_right
                    width: parent.width * 3
                    height: parent.height * 0.3  // Use only 30% of the parent's height at the bottom
                    anchors.bottom: parent.bottom  // Anchor to the bottom of the parent
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: parent.width
                    z: -5

                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.clearRect(0, 0, width, height); // Clear the canvas

                        // Set triangle color
                        ctx.fillStyle = "light green";

                        // Start drawing the right triangle at the bottom of the canvas
                        ctx.beginPath();
                        ctx.moveTo(0, height);           // Bottom-left corner
                        ctx.lineTo(width, height);       // Bottom-right corner
                        ctx.lineTo(0, 0);                // Top-left corner of the triangle
                        ctx.closePath();

                        // Fill the triangle
                        ctx.fill();
                    }
                }
            }
        }



    }

}
