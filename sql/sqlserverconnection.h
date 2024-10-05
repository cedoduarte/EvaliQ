#ifndef SQLSERVERCONNECTION_H
#define SQLSERVERCONNECTION_H

#include "../models/question.h"
#include "../models/candidate.h"

#include <QSqlDatabase>

#define QT_DATABASE_DRIVER "QODBC"
#define SQL_SERVER_CONNECTION_STRING "Driver={ODBC Driver 17 for SQL Server};Server=localhost\\SQLEXPRESS;Database=EvaliQ;Trusted_Connection=yes;TrustServerCertificate=yes;"

/**
 * @class SqlServerConnection
 * @brief Manages the connection to a SQL Server database.
 *
 * This class provides methods to connect, disconnect, and perform various operations
 * on the SQL Server database, such as inserting questions and candidates and
 * selecting questions from the database.
 */
class SqlServerConnection
{
public:
    /**
     * @brief Establishes a connection to the SQL Server.
     *
     * This method connects to the SQL Server database using the defined connection string.
     */
    static void connectServer();

    /**
     * @brief Disconnects from the SQL Server.
     *
     * This method closes the connection to the SQL Server database.
     */
    static void disconnectServer();

    /**
     * @brief Inserts a question into the database.
     *
     * @param question The question object to be inserted.
     * @return true if the insertion is successful, false otherwise.
     */
    static bool insertQuestion(const Question &question);

    /**
     * @brief Inserts a candidate into the database.
     *
     * @param candidate The candidate object to be inserted.
     * @return true if the insertion is successful, false otherwise.
     */
    static bool insertCandidate(const Candidate &candidate);

    /**
     * @brief Inserts default data into the database.
     *
     * This method populates the database with default values.
     */
    static void insertDefaultData();

    /**
     * @brief Selects all questions from the database.
     *
     * @return A vector containing all questions retrieved from the database.
     */
    static std::vector<Question> selectQuestions();

    /**
     * @brief Calculates the total points from the database.
     *
     * @return The total points as an integer.
     */
    static int totalPoints();

private:
    SqlServerConnection(); ///< Private constructor to prevent instantiation.

    /**
     * @brief Connects to the SQL Server database.
     *
     * @return true if the connection is successful, false otherwise.
     */
    bool connectToSqlServer();

    /**
     * @brief Disconnects from the SQL Server database.
     */
    void disconnectFromSqlServer();

    /**
     * @brief Checks if the specified table has rows.
     *
     * @param tableName The name of the table to check.
     * @return true if the table has rows, false otherwise.
     */
    bool hasRows(const QString &tableName);

    QSqlDatabase m_db; ///< The QSqlDatabase object used to manage the database connection.
    static SqlServerConnection *s_instance; ///< Singleton instance of SqlServerConnection.
};

#endif // SQLSERVERCONNECTION_H
