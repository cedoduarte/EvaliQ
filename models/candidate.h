#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

/**
 * @class Candidate
 * @brief Represents a candidate with personal information and performance metrics.
 */
class Candidate
{
public:
    /**
     * @brief Constructs a Candidate object with specified details.
     *
     * @param id The unique identifier for the candidate (primary key).
     * @param firstName The first name of the candidate.
     * @param lastName The last name of the candidate.
     * @param gainedPoints The points gained by the candidate.
     * @param rating The rating of the candidate.
     */
    Candidate(int id, const QString& firstName, const QString& lastName, int gainedPoints, float rating)
        : Id(id), FirstName(firstName), LastName(lastName), GainedPoints(gainedPoints), Rating(rating)
    {}

    /**
     * @brief Default constructor for a Candidate object.
     *
     * Initializes the candidate with default values (Id = 0, GainedPoints = 0, Rating = 0.0).
     */
    Candidate()
        : Id(0), GainedPoints(0), Rating(0.0f)
    {}

    /**
     * @brief Gets the unique identifier of the candidate.
     * @return The candidate's unique identifier (Id).
     */
    int getId() const
    {
        return Id;
    }

    /**
     * @brief Sets the unique identifier of the candidate.
     * @param id The new unique identifier for the candidate.
     */
    void setId(int id)
    {
        Id = id;
    }

    /**
     * @brief Gets the first name of the candidate.
     * @return The candidate's first name.
     */
    QString getFirstName() const
    {
        return FirstName;
    }

    /**
     * @brief Sets the first name of the candidate.
     * @param firstName The new first name for the candidate.
     */
    void setFirstName(const QString& firstName)
    {
        FirstName = firstName;
    }

    /**
     * @brief Gets the last name of the candidate.
     * @return The candidate's last name.
     */
    QString getLastName() const
    {
        return LastName;
    }

    /**
     * @brief Sets the last name of the candidate.
     * @param lastName The new last name for the candidate.
     */
    void setLastName(const QString& lastName)
    {
        LastName = lastName;
    }

    /**
     * @brief Gets the points gained by the candidate.
     * @return The points gained by the candidate.
     */
    int getGainedPoints() const
    {
        return GainedPoints;
    }

    /**
     * @brief Sets the points gained by the candidate.
     * @param gainedPoints The new points gained by the candidate.
     */
    void setGainedPoints(int gainedPoints)
    {
        GainedPoints = gainedPoints;
    }

    /**
     * @brief Gets the rating of the candidate.
     * @return The candidate's rating.
     */
    float getRating() const
    {
        return Rating;
    }

    /**
     * @brief Sets the rating of the candidate.
     * @param rating The new rating for the candidate.
     */
    void setRating(float rating)
    {
        Rating = rating;
    }
private:
    int Id;                   ///< The unique identifier for the candidate (primary key).
    QString FirstName;        ///< The first name of the candidate.
    QString LastName;         ///< The last name of the candidate.
    int GainedPoints;         ///< The points gained by the candidate.
    float Rating;             ///< The rating of the candidate.
};

#endif // CANDIDATE_H
