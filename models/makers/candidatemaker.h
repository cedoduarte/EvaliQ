#ifndef CANDIDATEMAKER_H
#define CANDIDATEMAKER_H

#include "../candidate.h"

/**
 * @class CandidateMaker
 * @brief A utility class for creating Candidate objects.
 */
class CandidateMaker
{
public:
    /**
     * @brief Constructs a CandidateMaker object.
     */
    CandidateMaker();

    /**
     * @brief Creates a Candidate object.
     *
     * This static method generates a Candidate object with the specified
     * first name, last name, gained points, and rating.
     *
     * @param firstName The first name of the candidate.
     * @param lastName The last name of the candidate.
     * @param gainedPoints The points gained by the candidate.
     * @param rating The rating of the candidate.
     * @return A Candidate object with the provided details.
     */
    static Candidate makeCandidate(const QString& firstName, const QString& lastName, int gainedPoints, float rating);
};

#endif // CANDIDATEMAKER_H

