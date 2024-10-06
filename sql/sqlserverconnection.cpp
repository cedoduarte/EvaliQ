#include "sqlserverconnection.h"
#include "../json/jsonfilereader.h"
#include "../models/makers/questionmaker.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

SqlServerConnection* SqlServerConnection::s_instance = nullptr;

void SqlServerConnection::connectServer()
{
    s_instance = new SqlServerConnection;
    s_instance->connectToSqlServer();
}

void SqlServerConnection::disconnectServer()
{
    if (s_instance)
    {
        s_instance->disconnectFromSqlServer();
        delete s_instance;
        s_instance = nullptr;
        qDebug() << "disconnected from SQL Server!";
    }
}

bool SqlServerConnection::insertQuestion(const Question &question)
{
    QSqlQuery query(s_instance->m_db);
    query.prepare("INSERT INTO Question (QuestionText, Category, Ponderation, CreatedAt, UpdatedAt, AnswerText) "
                  "VALUES (:text, :category, :ponderation, :createdAt, :updatedAt, :answer)");
    query.bindValue(":text", question.getText());
    query.bindValue(":category", question.getCategory());
    query.bindValue(":ponderation", question.getPonderation());
    query.bindValue(":createdAt", question.getCreatedAt());
    query.bindValue(":updatedAt", question.getUpdatedAt());
    query.bindValue(":answer", question.getAnswer());
    if (!query.exec())
    {
        qDebug() << "Error inserting question:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SqlServerConnection::insertCandidate(const Candidate &candidate)
{
    QSqlQuery query(s_instance->m_db);

    // Prepare the SQL insert statement
    query.prepare("INSERT INTO Candidate (FirstName, LastName, GainedPoints, Rating) "
                  "VALUES (:firstName, :lastName, :gainedPoints, :rating)");

    // Bind values from the Candidate object
    query.bindValue(":firstName", candidate.getFirstName());
    query.bindValue(":lastName", candidate.getLastName());
    query.bindValue(":gainedPoints", candidate.getGainedPoints());
    query.bindValue(":rating", candidate.getRating());

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error inserting candidate:" << query.lastError().text();
        return false;
    }

    return true;
}

bool SqlServerConnection::hasRows(const QString &tableName)
{
    QSqlQuery query;
    query.prepare(QString("SELECT COUNT(*) FROM %1").arg(tableName));
    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError();
        return false;
    }
    if (query.next())
    {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

void SqlServerConnection::insertDefaultData()
{
    if (!s_instance->hasRows("Question"))
    {
        JsonFileReader jsonReader;
        QJsonDocument doc = jsonReader.readFile(":/json/questions.json");
        QJsonArray questionArray = doc.array();
        for (const auto &questionValue : questionArray)
        {
            QJsonObject questionObject = questionValue.toObject();
            insertQuestion(QuestionMaker::makeQuestion(questionObject["text"].toString(),
                                                       questionObject["category"].toString(),
                                                       questionObject["points"].toDouble(),
                                                       questionObject["answer"].toString()));
        }
        qDebug() << "default data inserted...";
        return;
    }
    qDebug() << "no default data available!";
}

std::vector<Question> SqlServerConnection::selectQuestions()
{
    std::vector<Question> questionArray;
    QSqlQuery query;
    query.prepare("SELECT * FROM Question");
    query.exec();
    while (query.next())
    {
        questionArray.push_back(QuestionMaker::makeQuestion(query.value("questionText").toString(),
                                                            query.value("category").toString(),
                                                            query.value("ponderation").toDouble(),
                                                            query.value("answerText").toString()));
    }
    return questionArray;
}

int SqlServerConnection::totalPoints()
{
    QSqlQuery query;
    query.prepare("SELECT sum(Ponderation) FROM Question");
    query.exec();
    query.next();
    int totalPossiblePoints = query.value(0).toInt();
    return totalPossiblePoints;
}

SqlServerConnection::SqlServerConnection() {}

bool SqlServerConnection::connectToSqlServer()
{
    m_db = QSqlDatabase::addDatabase(QT_DATABASE_DRIVER);
    m_db.setDatabaseName(SQL_SERVER_CONNECTION_STRING);
    if (!m_db.open())
    {
        qDebug() << m_db.lastError().text();
        return false;
    }
    qDebug() << "connected to SQL Server successfully";
    return true;
}

void SqlServerConnection::disconnectFromSqlServer()
{
    m_db.close();
}
