#include "stats.h"
#include "ui_stats.h"
#include <QtWidgets/qpushbutton.h>

Stats::Stats(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Stats)
{
    ui->setupUi(this);
    this->setFixedSize(this->size()); // Lock window current size

    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, this, [this]() { // When player hits the reset button
        emit resetStatsRequested(); // Sends signal to main window that a reset was requested
    });
}

Stats::~Stats()
{
    delete ui;
}

// Set stats based on wins and losses
void Stats::setStats(int wins, int losses) {
    ui->wins->setText(QString::number(wins));   // Sets wins
    ui->losses->setText(QString::number(losses));   // Sets losses
    double winningPercentage = 0.0; // Winning percentage
    if (wins + losses > 0) {    // If winning + losses combo exceeds 0
        winningPercentage = static_cast<double>(wins) / (wins + losses) * 100.0;    // Get the percentage
    }
    QString percentString = QString::number(winningPercentage, 'f', 2) + "%";   /* Format it in a way that cuts most of the numbers after the dot,
    besides just two */
    ui->winningPercent->setText(percentString); // Set the formatted percentage in the text
}
