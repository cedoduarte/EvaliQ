import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    function getQuestionModel() {
        if (typeof mainWindow !== "undefined") {
            if (mainWindow) {
                return mainWindow.getQuestions();
            }
        }
        return null; // Ensure null is returned if mainWindow is undefined
    }

    property var questionModel: getQuestionModel()
    property int gainedPoints: 0
    property double rate: 0.0

    Component {
        id: questionDelegate
        Column {
            width: parent.width

            Text {
                text: `${index+1}. ${modelData.text}`
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "Arial"
                font.pointSize: 16
                width: parent.width
            }

            Text {
                text: modelData.answer
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "Arial"
                font.pointSize: 14
                width: parent.width
            }

            Row {
                property int points: 0
                property int previousPoints: 0
                property bool firstClick: true

                onPointsChanged: {
                    root.gainedPoints -= optionRow.previousPoints;
                    root.gainedPoints += optionRow.points;
                    mainWindow.setGainedPoints(root.gainedPoints);
                }

                id: optionRow
                Repeater {
                    model: modelData.points + 1
                    RadioButton {
                        id: optionButton
                        property int points: modelData
                        text: points
                        font.family: "Arial"
                        font.pointSize: 12
                        onClicked: {
                            if (optionRow.firstClick) {
                                optionRow.firstClick = false;
                                optionRow.points = optionButton.points;
                            } else {
                                optionRow.previousPoints = optionRow.points;
                            }
                            optionRow.points = optionButton.points;
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 10
        clip: true
        model: questionModel
        delegate: questionDelegate
        ScrollBar.vertical: ScrollBar {
            active: true
        }
    }
}

