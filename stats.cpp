#include "stats.h"
#include "qsettings.h"
#include "ui_stats.h"
#include <QtWidgets/qpushbutton.h>

Stats::Stats(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::Stats)
{
    ui->setupUi(this);
    this->showFullScreen(); // Make the window scale properly
    mw = w; // Set the reference to main window

    connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked, this, [this]() { // When player hits the reset button
        emit resetStatsRequested(); // Sends signal to main window that a reset was requested
    });
    WallpaperAssistant wa(this);    // Wallpaper assistaint
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    int wallpaperID = settings.value("wallpaperID", 2).toInt(); // Set wallpaperID to match the currently set wallpaper
    wa.changeWallpaper(wallpaperID);    // Set the wallpaper
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

// Change windows/tabs
void Stats::on_tabWidget_currentChanged(int index)
{
    mw->on_tabWidget_currentChanged(index); // Open the new window(via main window)
    this->close();  // Close this window
}

