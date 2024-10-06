#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../sql/sqlserverconnection.h"
#include "../models/makers/questionmaker.h"
#include "../enums/enums.h"
#include "savecandidatedialog.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QQmlEngine>
#include <QQmlContext>
#include <QMessageBox>
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SqlServerConnection::connectServer();
    SqlServerConnection::insertDefaultData();

    m_questionModel = new QSqlTableModel(this);
    m_questionModel->setTable("Question");
    m_questionModel->select();
    ui->questionTableView->setModel(m_questionModel);
    ui->questionTableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_deleteQuestionAction = new QAction("Delete", this);
    m_deleteQuestionAction->setIcon(QIcon(":/img/remove.png"));
    ui->questionTableView->addAction(m_deleteQuestionAction);
    connect(m_deleteQuestionAction, &QAction::triggered, this, &MainWindow::handleDeleteQuestion);

    m_candidateModel = new QSqlTableModel(this);
    m_candidateModel->setTable("Candidate");
    m_candidateModel->select();
    ui->candidateTableView->setModel(m_candidateModel);
    ui->candidateTableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_deleteCandidateAction = new QAction("Delete", this);
    m_deleteCandidateAction->setIcon(QIcon(":/img/remove.png"));
    ui->candidateTableView->addAction(m_deleteCandidateAction);
    connect(m_deleteCandidateAction, &QAction::triggered, this, &MainWindow::handleDeleteCandidate);

    ui->questionOptionListWidget->item(0)->setData(Qt::UserRole, InsertQuestion);
    ui->questionOptionListWidget->item(1)->setData(Qt::UserRole, EditQuestions);

    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/QuestionView.qml")));
    if (ui->quickWidget->status() == QQuickWidget::Error)
    {
        qWarning() << "Error loading QML:" << ui->quickWidget->errors();
    }
    ui->quickWidget->engine()->rootContext()->setContextProperty("mainWindow", this);


    // Set initial sizes, 116px for the first widget, and the second one gets the remaining space
    QList<int> sizes;
    sizes << 140 << 1;  // First widget gets 116px, second gets some small size initially
    ui->splitter->setSizes(sizes);

    // Set the second widget to stretch and take up the remaining space
    ui->splitter->setStretchFactor(0, 0);  // First widget doesn't stretch
    ui->splitter->setStretchFactor(1, 1);  // Second widget stretches to take remaining space

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SqlServerConnection::disconnectServer();
    QMainWindow::closeEvent(event);
}

QVariantList MainWindow::getQuestions()
{
    QVariantList questionArray;
    for (const auto &question : SqlServerConnection::selectQuestions())
    {
        QVariantMap questionObject;
        questionObject["text"] = question.getText();
        questionObject["category"] = question.getCategory();
        questionObject["points"] = question.getPonderation();
        questionObject["answer"] = question.getAnswer();
        questionArray.append(questionObject);
    }
    return questionArray;
}

void MainWindow::setGainedPoints(int points)
{
    m_gainedPoints = points;
    ui->txtGainedPoints->setText(QString::number(points));
    computeRating();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_buttonInsertQuestion_clicked()
{
    if (SqlServerConnection::insertQuestion(QuestionMaker::makeQuestion(ui->txtQuestionText->toPlainText(),
                                                                        ui->comboQuestionCategory->currentText(),
                                                                        ui->txtQuestionPonderation->text().toDouble(),
                                                                        ui->txtQuestionAnswerText->toPlainText())))
    {
        emit questionTableUpdated();
        ui->statusbar->showMessage("Question inserted...");
    }
    else
    {
        ui->statusbar->showMessage("Question not inserted!");
    }
}

void MainWindow::on_buttonClearQuestion_clicked()
{
    ui->txtQuestionText->clear();
    ui->txtQuestionPonderation->clear();
}

void MainWindow::on_questionOptionListWidget_itemClicked(QListWidgetItem *item)
{
    switch (item->data(Qt::UserRole).toInt())
    {
        case InsertQuestion:
            ui->questionStackedWidget->setCurrentWidget(ui->insertQuestionWidget);
            break;
        case EditQuestions:
            ui->questionStackedWidget->setCurrentWidget(ui->editQuestionWidget);
            break;
    }
}

void MainWindow::computeRating()
{
    int totalPossiblePoints = SqlServerConnection::totalPoints();
    m_rating = double(m_gainedPoints) / double(totalPossiblePoints) * 100.0;
    ui->txtRating->setText(QString("%1%").arg(m_rating));
}

void MainWindow::on_buttonSaveCandidateResult_clicked()
{
    if (ui->txtGainedPoints->text().isEmpty() || ui->txtRating->text().isEmpty())
    {
        return;
    }
    SaveCandidateDialog saveDialog(this);
    saveDialog.setGainedPoints(m_gainedPoints);
    saveDialog.setRating(m_rating);
    if (saveDialog.exec() == QDialog::Accepted)
    {
        Candidate candidate = saveDialog.getCandidate();
        if (candidate.getFirstName().isEmpty() || candidate.getLastName().isEmpty())
        {
            QMessageBox::critical(this, "Error", "The first name or last name is empty!");
            return;
        }
        if (SqlServerConnection::insertCandidate(candidate))
        {
            QMessageBox::information(this, "OK", "Operation concluded successfully!");
            m_candidateModel->select();
        }
    }
}

void MainWindow::handleDeleteCandidate()
{
    handleDeleteEntity(ui->candidateTableView, m_candidateModel);
}

void MainWindow::handleDeleteQuestion()
{
    if (handleDeleteEntity(ui->questionTableView, m_questionModel))
    {
        emit questionTableUpdated();
    }
}

bool MainWindow::handleDeleteEntity(QTableView *tableView, QSqlTableModel *tableModel)
{
    int row = tableView->currentIndex().row();
    if (QMessageBox::question(this, "Question",
        QString("Are you sure to delete the row %1").arg(row+1)) == QMessageBox::Yes)
    {
        if (tableModel->removeRows(row, 1))
        {
            tableModel->select();
        }
        else
        {
            QMessageBox::warning(this, "Error", "The row was not deleted!");
            return false;
        }
    }
    return true;
}
