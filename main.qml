import QtQuick
import QtQuick.Controls

import Ext

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    readonly property int cellWidth: 60

    Board {
        id: boardGame
    }



    Column {
        width: parent.width
        anchors.centerIn: parent
        spacing: 20
        visible: boardGame.gameState == Board.Playing
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: xPlayer.width + 10
                height: xPlayer.height + 20
                Text {
                    id: xPlayer
                    anchors.centerIn: parent
                    text: qsTr("Player X")
                }

                color: boardGame.currentPlayer == Board.Cross ? "green"
                                                              : "transparent"
            }

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: oPlayer.width + 10
                height: oPlayer.height + 20
                Text {
                    id: oPlayer
                    anchors.centerIn: parent
                    text: qsTr("Player O")
                }

                color: boardGame.currentPlayer == Board.Zero ? "green"
                                                             : "transparent"
            }
        }

        Flow {
            anchors.horizontalCenter: parent.horizontalCenter
            width: boardGame.size * cellWidth
            height: boardGame.size * cellWidth
            Repeater {
                model: boardGame.size * boardGame.size
                delegate: Rectangle {
                    width: cellWidth
                    height: width
                    color: "white"
                    border.color: "black"

                    Text {
                        id: text
                        anchors.centerIn: parent
                        font.pixelSize: 30
                        font.bold: true

                        Connections {
                            target: boardGame
                            function onGameStateChanged() {
                                if (boardGame.gameState == Board.Playing) {
                                    text.text = ""
                                }
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            let figure = boardGame.move(index)
                            switch (figure) {
                            case Board.Empty:
                                text.text = ""
                                return
                            case Board.Cross:
                                text.text = "X"
                                return
                            case Board.Zero:
                                text.text = "O"
                                return
                            }
                        }
                    }
                }
            }

            opacity: boardGame.gameState == Board.Playing ? 1.0 : 0.5
        } // Flow
    }

    Popup {
        anchors.centerIn: parent
        width: 300
        height: 300
        modal: true
        visible: boardGame.gameState != Board.Playing

        contentItem: Column {
            anchors.centerIn: parent
            spacing: 10
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                text: {
                    switch (boardGame.gameState) {
                    case Board.Idle:
                        return qsTr("Press start please!")
                    case Board.Tie:
                        return qsTr("Its tie! start new game")
                    case Board.PlayerXWin:
                        return qsTr("Player X WIN!")
                    case Board.PlayerOWin:
                        return qsTr("Player O WIN!")
                    default:
                        return ""
                    }
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Start")
                onClicked: boardGame.start()
            }
        }
    }
}
