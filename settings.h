#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(MainWindow *w = nullptr);
    ~Settings();

    void updateDefault(int index);  // Update selected preset in the listView

private slots:
    void on_setPlayerName_clicked();    // When player clicks "Set" near the newly set player name

    void on_setDealerName_clicked();    // When player clicks "Set" near the newly set dealer name

    void on_enableSound_currentIndexChanged(int index); // When player changes the sound settings

    void on_tabWidget_currentChanged(int index);    // Change tabs/windows

private:
    Ui::Settings *ui;
    MainWindow *mw; // Reference to the main window
    void loadSave();    // Load data from saves
    void save();    // Save data
    QString playerName = "Player";  // Player name
    QString dealerName = "Dealer";  // Dealer name
    bool enableSounds = true;   // Whether sound is enabled or not
    int defaultAiMode;  // Original AI mode before any modifications were done
};

#endif // SETTINGS_H
