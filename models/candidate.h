#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

class Candidate {
public:


    // Constructor
    Candidate(int id, const QString& firstName, const QString& lastName, int gainedPoints, float rating)
        : Id(id), FirstName(firstName), LastName(lastName), GainedPoints(gainedPoints), Rating(rating) {}

    // Default constructor
    Candidate() : Id(0), GainedPoints(0), Rating(0.0f) {}

    // Optional: Add getters and setters if needed
    int getId() const { return Id; }
    void setId(int id) { Id = id; }

    QString getFirstName() const { return FirstName; }
    void setFirstName(const QString& firstName) { FirstName = firstName; }

    QString getLastName() const { return LastName; }
    void setLastName(const QString& lastName) { LastName = lastName; }

    int getGainedPoints() const { return GainedPoints; }
    void setGainedPoints(int gainedPoints) { GainedPoints = gainedPoints; }

    float getRating() const { return Rating; }
    void setRating(float rating) { Rating = rating; }
private:
    // Member variables corresponding to the table columns
    int Id;                   // Primary Key
    QString FirstName;        // First Name
    QString LastName;         // Last Name
    int GainedPoints;         // Gained Points
    float Rating;             // Rating
};

#endif // CANDIDATE_H
