#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../sql/sqlserverconnection.h"
#include "../makers/questionmaker.h"
#include "../enums/enums.h"
#include "savecandidatedialog.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QQmlEngine>
#include <QQmlContext>
#include <QMessageBox>

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

    ui->questionOptionListWidget->item(0)->setData(Qt::UserRole, InsertQuestion);
    ui->questionOptionListWidget->item(1)->setData(Qt::UserRole, EditQuestions);

    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/QuestionView.qml")));
    if (ui->quickWidget->status() == QQuickWidget::Error)
    {
        qWarning() << "Error loading QML:" << ui->quickWidget->errors();
    }
    ui->quickWidget->engine()->rootContext()->setContextProperty("mainWindow", this);
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
        }
    }
}
