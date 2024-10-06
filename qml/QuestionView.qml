/**
 * @file QuestionView.qml
 * @brief View for displaying questions and managing user interactions.
 *
 * This file defines a user interface for displaying a list of questions,
 * handling user answers, and updating the score based on selections.
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

/**
 * @class QuestionView
 * @brief The main view for presenting questions to the user.
 *
 * This view manages a list of questions and user interactions with multiple-choice answers.
 */
Item {
    id: root

    /**
     * @brief Retrieves the question model from the main window.
     *
     * This function checks if the main window is defined and returns the questions.
     * @return The question model if mainWindow is defined, otherwise null.
     */
    function getQuestionModel() {
        if (typeof mainWindow !== "undefined") {
            if (mainWindow) {
                return mainWindow.getQuestions();
            }
        }
        return null; // Ensure null is returned if mainWindow is undefined
    }

    Connections {
        target: {
            if (typeof mainWindow !== "undefined") {
                return mainWindow;
            }
            return null;
        }

        function onQuestionTableUpdated() {
            root.questionModel = root.getQuestionModel();
        }
    }

    /**
     * @property questionModel
     * @brief The model of questions to be displayed in the view.
     *
     * This property retrieves the question model using the getQuestionModel function.
     */
    property var questionModel: getQuestionModel()

    /**
     * @property gainedPoints
     * @brief The total points gained by the user based on answers.
     */
    property int gainedPoints: 0

    /**
     * @property rate
     * @brief The rating or score assigned to the user's performance.
     */
    property double rate: 0.0

    /**
     * @brief Delegate for displaying each question and its options.
     */
    Component {
        id: questionDelegate

        Column {
            width: parent.width

            /**
             * @brief Displays the question text.
             */
            Text {
                text: `${index + 1}. ${modelData.text}`
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "Arial"
                font.pointSize: 16
                width: parent.width
            }

            /**
             * @brief Displays the answer for the question.
             */
            Text {
                text: modelData.answer
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "Arial"
                font.pointSize: 14
                width: parent.width
            }

            Row {
                /**
                 * @brief Properties to manage points for the current question.
                 */
                property int points: 0
                property int previousPoints: 0
                property bool firstClick: true

                /**
                 * @brief Updates gained points when points property changes.
                 */
                onPointsChanged: {
                    root.gainedPoints -= optionRow.previousPoints;
                    root.gainedPoints += optionRow.points;
                    mainWindow.setGainedPoints(root.gainedPoints);
                }

                id: optionRow

                /**
                 * @brief Repeater for generating radio buttons for answer options.
                 */
                Repeater {
                    model: modelData.points + 1
                    RadioButton {
                        id: optionButton
                        property int points: modelData
                        text: points
                        font.family: "Arial"
                        font.pointSize: 12

                        /**
                         * @brief Handles click events on radio buttons.
                         *
                         * Updates points based on user selection and manages first click behavior.
                         */
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

    /**
     * @brief List view for displaying questions and managing user selections.
     */
    ListView {
        id: listView
        anchors.fill: parent
        spacing: 10
        clip: true
        model: questionModel
        delegate: questionDelegate

        /**
         * @brief Vertical scrollbar for the list view.
         */
        ScrollBar.vertical: ScrollBar {
            active: true
        }
    }
}
