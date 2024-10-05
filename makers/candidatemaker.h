#ifndef CANDIDATEMAKER_H
#define CANDIDATEMAKER_H

#include "../models/candidate.h"

class CandidateMaker
{
public:
    CandidateMaker();
    static Candidate makeCandidate(const QString& firstName, const QString& lastName, int gainedPoints, float rating);
};

#endif // CANDIDATEMAKER_H
