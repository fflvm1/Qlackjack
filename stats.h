#ifndef STATS_H
#define STATS_H

#include <QDialog>

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

    void setStats(int wins, int losses);    // Set stats to match main window's variables

private:
    Ui::Stats *ui;
signals:
    void resetStatsRequested(); // Request resetting stats
};

#endif // STATS_H
