#include "questionmaker.h"

QuestionMaker::QuestionMaker() {}

Question QuestionMaker::makeQuestion(const QString &text, const QString &category, double ponderation, const QString &answer)
{
    Question question;
    question.setText(text);
    question.setCategory(category);
    question.setPonderation(ponderation);
    question.setAnswer(answer);
    return question;
}
