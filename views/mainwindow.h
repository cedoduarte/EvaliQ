#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariantList>

class QListWidgetItem;
class QSqlTableModel;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
public slots:
    QVariantList getQuestions();
    void setGainedPoints(int points);
private slots:
    void on_actionClose_triggered();

    void on_buttonInsertQuestion_clicked();

    void on_buttonClearQuestion_clicked();

    void on_questionOptionListWidget_itemClicked(QListWidgetItem *item);

    void on_buttonSaveCandidateResult_clicked();

private:
    void computeRating();

    Ui::MainWindow *ui;
    QSqlTableModel *m_questionModel;
    int m_gainedPoints;
    double m_rating;
};

#endif // MAINWINDOW_H
