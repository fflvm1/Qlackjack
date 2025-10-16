#include "settings.h"
#include "ui_settings.h"
#include <QtCore/qsettings.h>

Settings::Settings(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::Settings)
{
    mw = w; // Save reference to main window
    ui->setupUi(this);
    this->setFixedSize(this->size()); // Lock window current size
    loadSave(); // Load saved data
    defaultAiMode = mw->aiMode; // Save the AI preset used before modifications in the settings
}

// Upon window's deletion
Settings::~Settings()
{
    mw->aiMode = ui->listWidget->currentRow();  // Change the AI mode in the mainwindow
    save(); // Save the game + reinitialise
    delete ui;
}

// When a new player name is to be set
void Settings::on_setPlayerName_clicked()
{
    playerName = ui->playerName->toPlainText(); // Update the self-titled variable
}

// When a new dealer name is to be set
void Settings::on_setDealerName_clicked()
{
    dealerName = ui->dealerName->toPlainText(); // Update the self-titled variable
}

// When player changes the state of sound via comboBox
void Settings::on_enableSound_currentIndexChanged(int index)
{
    switch(index) { // Switch on the index
        case 0:{    // Index 0: Enable sound(default)
            enableSounds = true;    // Set the self-titled variable to true
            break;
        }
        case 1:{    // Index 1: Disable sound
            enableSounds = false;   // Set the self-titled variable to false, indicating that sound is to be disabled
            break;
        }
    }
}

// Load data from the save
void Settings::loadSave() {
    QSettings settings("FFNETWORK", "Qlackjack");   // Where to load from
    playerName = settings.value("playerName", "Player").toString(); // Get the player name
    ui->playerName->setPlainText(playerName);   // Set it inside of the editing box
    dealerName = settings.value("dealerName", "Dealer").toString(); // Get the dealer name
    ui->dealerName->setPlainText(dealerName);   // Same thing here
    enableSounds = settings.value("enableSounds", true).toBool();   // Get whether sounds are enabled or not
    if (enableSounds) {
        ui->enableSound->setCurrentIndex(0);    // If they are, set enableSound to "Yes"
    }   else {
        ui->enableSound->setCurrentIndex(1);    // If they aren't, set it to "No"
    }
}

// Save game
void Settings::save() {
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    settings.setValue("playerName", playerName);    // Update the player name
    settings.setValue("dealerName", dealerName);    // Update the dealer name
    settings.setValue("enableSounds", enableSounds);    // Update the sound preferences
    mw->playerName = playerName;    // Change the player name in the main window
    mw->dealerName = dealerName;    // Same for the dealer name
    mw->loadStats();    // Load stats
    if (defaultAiMode != ui->listWidget->currentRow()) {
        mw->initialise();   // Only reinitisialise the game if AI preset has been changed
    }
}

// Update default selection to match the current selected mode
void Settings::updateDefault(int index) {
    ui->listWidget->setCurrentRow(index);   // Set the selected row
}
