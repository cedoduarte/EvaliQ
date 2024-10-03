#ifndef SQLSERVERCONNECTION_H
#define SQLSERVERCONNECTION_H

#include "../models/question.h"

#include <QSqlDatabase>

#define QT_DATABASE_DRIVER "QODBC"
#define SQL_SERVER_CONNECTION_STRING "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=EvaliQ;Trusted_Connection=yes;TrustServerCertificate=yes;"

class SqlServerConnection
{
public:
    static void connectServer();
    static void disconnectServer();

    /**
     * @brief Inserts a question into the database.
     *
     * @param db The database connection to use.
     * @param question The `Question` object containing the data to insert.
     * @return true if the insertion was successful, false otherwise.
     */
    static bool insertQuestion(const Question &question);

    static void insertDefaultData();

    static std::vector<Question> selectQuestions();
private:
    SqlServerConnection();
    bool connectToSqlServer();
    void disconnectFromSqlServer();
    bool hasRows(const QString &tableName);

    QSqlDatabase m_db;
    static SqlServerConnection *s_instance;
};

#endif // SQLSERVERCONNECTION_H
