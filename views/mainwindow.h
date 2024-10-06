#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariantList>

class QListWidgetItem;
class QSqlTableModel;
class QAction;
class QTableView;

namespace Ui
{
class MainWindow;
}

/**
 * @class MainWindow
 * @brief The main application window for managing candidates and questions.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a MainWindow object.
     *
     * @param parent Optional parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructs the MainWindow object.
     */
    ~MainWindow();
protected:
    /**
     * @brief Handles the close event of the window.
     *
     * @param event The close event.
     */
    void closeEvent(QCloseEvent *event) override;
signals:
    void questionTableUpdated();
public slots:
    /**
     * @brief Retrieves the list of questions.
     * @return A QVariantList containing the questions.
     */
    QVariantList getQuestions();

    /**
     * @brief Sets the gained points for the candidate.
     *
     * @param points The gained points to set.
     */
    void setGainedPoints(int points);
private slots:
    /**
     * @brief Handles the action triggered to close the application.
     */
    void on_actionClose_triggered();

    /**
     * @brief Handles the button click event for inserting a question.
     */
    void on_buttonInsertQuestion_clicked();

    /**
     * @brief Handles the button click event for clearing a question.
     */
    void on_buttonClearQuestion_clicked();

    /**
     * @brief Handles the item click event in the question option list widget.
     *
     * @param item The clicked QListWidgetItem.
     */
    void on_questionOptionListWidget_itemClicked(QListWidgetItem *item);

    /**
     * @brief Handles the button click event for saving the candidate's result.
     */
    void on_buttonSaveCandidateResult_clicked();

    void handleDeleteCandidate();
    void handleDeleteQuestion();
private:
    /**
     * @brief Computes the rating based on gained points.
     */
    void computeRating();

    bool handleDeleteEntity(QTableView *tableView, QSqlTableModel *tableModel);

    Ui::MainWindow *ui;          ///< Pointer to the UI elements of the MainWindow.
    QSqlTableModel *m_questionModel; ///< Model for managing questions in the database.
    QSqlTableModel *m_candidateModel;
    int m_gainedPoints;          ///< Points gained by the candidate.
    double m_rating;             ///< Rating of the candidate based on gained points.
    QAction *m_deleteCandidateAction;
    QAction *m_deleteQuestionAction;
};

#endif // MAINWINDOW_H
