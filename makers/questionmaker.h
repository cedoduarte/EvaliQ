#ifndef QUESTIONMAKER_H
#define QUESTIONMAKER_H

#include "../models/question.h"

class QuestionMaker
{
public:
    QuestionMaker();
    static Question makeQuestion(const QString &text, const QString &category, double ponderation, const QString &answer);
};

#endif // QUESTIONMAKER_H
