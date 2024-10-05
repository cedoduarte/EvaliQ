#ifndef SAVECANDIDATEDIALOG_H
#define SAVECANDIDATEDIALOG_H

#include "../models/candidate.h"

#include <QDialog>

namespace Ui
{
class SaveCandidateDialog;
}

/**
 * @class SaveCandidateDialog
 * @brief Dialog for saving candidate information.
 */
class SaveCandidateDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a SaveCandidateDialog object.
     *
     * @param parent Optional parent widget.
     */
    explicit SaveCandidateDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructs the SaveCandidateDialog object.
     */
    ~SaveCandidateDialog();

    /**
     * @brief Sets the gained points for the candidate.
     *
     * @param points The gained points to set.
     */
    void setGainedPoints(int points);

    /**
     * @brief Sets the rating for the candidate.
     *
     * @param rating The rating to set.
     */
    void setRating(double rating);

    /**
     * @brief Gets the candidate object with the current values.
     *
     * @return A Candidate object populated with the dialog's data.
     */
    Candidate getCandidate() const;
private slots:
    /**
     * @brief Handles the acceptance of the dialog.
     * This slot is triggered when the user clicks the accept button.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Handles the rejection of the dialog.
     * This slot is triggered when the user clicks the reject button.
     */
    void on_buttonBox_rejected();
private:
    Ui::SaveCandidateDialog *ui; ///< Pointer to the UI elements of the dialog.
    int m_gainedPoints;           ///< Points gained by the candidate.
    double m_rating;              ///< Rating of the candidate.
};

#endif // SAVECANDIDATEDIALOG_H

