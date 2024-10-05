#ifndef SAVECANDIDATEDIALOG_H
#define SAVECANDIDATEDIALOG_H

#include "../models/candidate.h"

#include <QDialog>

namespace Ui {
class SaveCandidateDialog;
}

class SaveCandidateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveCandidateDialog(QWidget *parent = nullptr);
    ~SaveCandidateDialog();
    void setGainedPoints(int points);
    void setRating(double rating);
    Candidate getCandidate() const;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::SaveCandidateDialog *ui;
    int m_gainedPoints;
    double m_rating;
};

#endif // SAVECANDIDATEDIALOG_H
