#include "candidatemaker.h"

CandidateMaker::CandidateMaker() {}

Candidate CandidateMaker::makeCandidate(const QString &firstName, const QString &lastName, int gainedPoints, float rating)
{
    Candidate candidate;
    candidate.setFirstName(firstName);
    candidate.setLastName(lastName);
    candidate.setGainedPoints(gainedPoints);
    candidate.setRating(rating);
    return candidate;
}
