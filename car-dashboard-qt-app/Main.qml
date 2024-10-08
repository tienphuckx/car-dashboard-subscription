import QtQuick
import QtMultimedia

Window {
    width: 920
    height: 670
    visible: true
    title: qsTr("Car Dashboard Subscription")
    color: "black"
    visibility: Window.FullScreen

    Video {
        id: backgroundVideo
        anchors.fill: parent
        source: "qrc:/img/fi_bg.mp4"
        loops: MediaPlayer.Infinite
        fillMode: VideoOutput.PreserveAspectCrop
        Component.onCompleted: {
            backgroundVideo.play()
        }
    }

    SoundEffect {
        id: sound_run
        source: "qrc:/img/noisy_car_sound.wav"
        volume: 1
        loops: 1
    }

    SoundEffect {
        id: sound_start
        source: "qrc:/img/sound/start.wav"
        volume: 1

        /** Play sound running car after finish start car */
        onPlayingChanged: {
            if (!playing) {
                sound_run.play();
            }
        }
    }

    Dashboard {
        width: 720
        height: 470


        anchors {
            // horizontalCenter: parent.horizontalCenter
            // verticalCenter: parent.verticalCenter
            left: parent.left
            top: parent.top
            topMargin: 210
            // rightMargin: 200
        }

        Component.onCompleted: {
            sound_start.play();
        }
    }

}

