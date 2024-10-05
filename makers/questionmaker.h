#ifndef QUESTIONMAKER_H
#define QUESTIONMAKER_H

#include "../models/question.h"

/**
 * @class QuestionMaker
 * @brief A utility class for creating Question objects.
 */
class QuestionMaker
{
public:
    /**
     * @brief Constructs a QuestionMaker object.
     */
    QuestionMaker();

    /**
     * @brief Creates a Question object.
     *
     * This static method generates a Question object with the specified
     * text, category, ponderation, and answer.
     *
     * @param text The text of the question.
     * @param category The category to which the question belongs.
     * @param ponderation The weight or importance of the question.
     * @param answer The correct answer for the question.
     * @return A Question object with the provided details.
     */
    static Question makeQuestion(const QString &text, const QString &category, double ponderation, const QString &answer);
};

#endif // QUESTIONMAKER_H

