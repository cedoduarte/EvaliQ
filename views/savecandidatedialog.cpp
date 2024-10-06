#include "savecandidatedialog.h"
#include "ui_savecandidatedialog.h"
#include "../models/makers/candidatemaker.h"

SaveCandidateDialog::SaveCandidateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SaveCandidateDialog)
{
    ui->setupUi(this);
}

SaveCandidateDialog::~SaveCandidateDialog()
{
    delete ui;
}

void SaveCandidateDialog::setGainedPoints(int points)
{
    m_gainedPoints = points;
    ui->txtGainedPoints->setText(QString::number(m_gainedPoints));
}

void SaveCandidateDialog::setRating(double rating)
{
    m_rating = rating;
    ui->txtRating->setText(QString::number(m_rating, 'f'));
}

Candidate SaveCandidateDialog::getCandidate() const
{
    return CandidateMaker::makeCandidate(ui->txtFirstName->text(), ui->txtLastName->text(), m_gainedPoints, m_rating);
}

void SaveCandidateDialog::on_buttonBox_accepted()
{
    accept();
}

void SaveCandidateDialog::on_buttonBox_rejected()
{
    close();
}

