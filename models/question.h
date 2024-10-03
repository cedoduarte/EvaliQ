#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QDateTime>

/**
 * @class Question
 * @brief Represents a question entity with attributes matching the SQL table structure.
 *
 * This class models a question that can be stored in a database table.
 * It includes information like the question text, category, ponderation (weight),
 * and timestamps for creation and last update.
 */
class Question
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes a new `Question` object with default values.
     * - `m_id` is initialized to 0.
     * - `m_text`, `m_category` are initialized to empty strings.
     * - `m_ponderation` is initialized to 0.0.
     * - `m_createdAt` and `m_updatedAt` are initialized to the current date and time.
     */
    Question()
        : m_id(0), m_text(""), m_category(""), m_ponderation(0.0), m_answer(""),
        m_createdAt(QDateTime::currentDateTime()), m_updatedAt(QDateTime::currentDateTime())
    {
    }

    /**
     * @brief Parameterized constructor.
     *
     * Initializes a new `Question` object with the provided values.
     *
     * @param id The unique identifier for the question (QuestionID).
     * @param text The text of the question.
     * @param category The category or topic of the question.
     * @param ponderation The weight or ponderation of the question.
     * @param createdAt The date and time when the question was created.
     * @param updatedAt The date and time when the question was last updated.
     */
    Question(int id, const QString &text, const QString &category, double ponderation, const QString &answer,
             const QDateTime &createdAt, const QDateTime &updatedAt)
        : m_id(id), m_text(text), m_category(category), m_ponderation(ponderation),
        m_createdAt(createdAt), m_updatedAt(updatedAt)
    {
    }

    /**
     * @brief Gets the question ID.
     * @return The unique identifier (QuestionID).
     */
    int getId() const
    {
        return m_id;
    }

    /**
     * @brief Sets the question ID.
     * @param id The unique identifier (QuestionID) to be set.
     */
    void setId(int id)
    {
        m_id = id;
    }

    /**
     * @brief Gets the text of the question.
     * @return The question text.
     */
    QString getText() const
    {
        return m_text;
    }

    /**
     * @brief Sets the text of the question.
     * @param text The text of the question to be set.
     */
    void setText(const QString &text)
    {
        m_text = text;
    }

    /**
     * @brief Gets the category of the question.
     * @return The category or topic of the question.
     */
    QString getCategory() const
    {
        return m_category;
    }

    /**
     * @brief Sets the category of the question.
     * @param category The category or topic of the question to be set.
     */
    void setCategory(const QString &category)
    {
        m_category = category;
    }

    /**
     * @brief Gets the ponderation (weight) of the question.
     * @return The ponderation of the question.
     */
    double getPonderation() const
    {
        return m_ponderation;
    }

    /**
     * @brief Sets the ponderation (weight) of the question.
     * @param ponderation The ponderation of the question to be set.
     */
    void setPonderation(double ponderation)
    {
        m_ponderation = ponderation;
    }

    /**
     * @brief Gets the creation timestamp of the question.
     * @return The `QDateTime` when the question was created.
     */
    QDateTime getCreatedAt() const
    {
        return m_createdAt;
    }

    /**
     * @brief Sets the creation timestamp of the question.
     * @param createdAt The `QDateTime` of when the question was created.
     */
    void setCreatedAt(const QDateTime &createdAt)
    {
        m_createdAt = createdAt;
    }

    /**
     * @brief Gets the last updated timestamp of the question.
     * @return The `QDateTime` when the question was last updated.
     */
    QDateTime getUpdatedAt() const
    {
        return m_updatedAt;
    }

    /**
     * @brief Sets the last updated timestamp of the question.
     * @param updatedAt The `QDateTime` of when the question was last updated.
     */
    void setUpdatedAt(const QDateTime &updatedAt)
    {
        m_updatedAt = updatedAt;
    }

    QString getAnswer() const
    {
        return m_answer;
    }

    void setAnswer(const QString &answer)
    {
        m_answer = answer;
    }
private:
    int m_id;                  /**< Unique identifier for the question (QuestionID) */
    QString m_text;            /**< Text of the question */
    QString m_category;        /**< Category or topic of the question */
    double m_ponderation;      /**< Ponderation (weight) of the question */
    QString m_answer;
    QDateTime m_createdAt;     /**< Timestamp of when the question was created */
    QDateTime m_updatedAt;     /**< Timestamp of when the question was last updated */
};

#endif // QUESTION_H
