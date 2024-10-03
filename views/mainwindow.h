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
private slots:
    void on_actionClose_triggered();

    void on_buttonInsertQuestion_clicked();

    void on_buttonClearQuestion_clicked();

    void on_questionOptionListWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *m_questionModel;
};

#endif // MAINWINDOW_H
