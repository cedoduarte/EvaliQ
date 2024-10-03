import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    ListView {
        id: listView
        anchors.fill: parent

        model: {
            if (typeof mainWindow !== "undefined") {
                if (mainWindow) {
                    return mainWindow.getQuestions();
                }
            } else {
                return null;
            }
        }

        spacing: 10
        delegate: Column {
            width: listView.width

            Text {
                text: modelData.text
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Text {
                text: modelData.answer
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }
    }
}
