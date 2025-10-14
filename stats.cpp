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
}
