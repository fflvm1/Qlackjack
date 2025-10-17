#ifndef STATS_H
#define STATS_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Stats(MainWindow* w = nullptr);
    ~Stats();

    void setStats(int wins, int losses);    // Set stats to match main window's variables

private:
    Ui::Stats *ui;
    MainWindow* mw; // Reference to main window
signals:
    void resetStatsRequested(); // Request resetting stats
private slots:
    void on_tabWidget_currentChanged(int index);    // Change tabs/windows
};

#endif // STATS_H
