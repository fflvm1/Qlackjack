#include "wallpapersettings.h"
#include "ui_wallpapersettings.h"
#include <QtCore/qsettings.h>

#include <QFileDialog>
#include <QStandardPaths>

WallpaperSettings::WallpaperSettings(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::WallpaperSettings)
{
    ui->setupUi(this);
    mw = w; // Save reference to main window
    this->setFixedSize(600, 300); // Lock current size
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    wallpaperID = settings.value("wallpaperID", 2).toInt(); // Set wallpaperID to match the currently set wallpaper
}

// When window is removed
WallpaperSettings::~WallpaperSettings()
{
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    settings.setValue("wallpaperID", wallpaperID);  // Change saves wallpaper ID to the variable
    mw->loadStats();    // Load the save inside of the main window to update the wallpaper
    delete ui;
}

// When first background is chosen
void WallpaperSettings::on_bg1_clicked()
{
    wallpaperID = 1;
    mw->changeWallpaper(1); // Set the background to the first one
}

// When second background is chosen
void WallpaperSettings::on_bg2_clicked()
{
    wallpaperID = 2;
    mw->changeWallpaper(2); // Set the background to the second one
}

// When third background is chosen
void WallpaperSettings::on_bg_3_clicked()
{
    wallpaperID = 3;
    mw->changeWallpaper(3); // Set the background to the third one
}

// When player chooses a custom background
void WallpaperSettings::on_custom_bg_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(    // Summon a dialogue to let player choose a background
        this,
        "Choose a Wallpaper",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );

    if (!filePath.isEmpty()) {  // Check if it's a valid path
        QSettings settings("FFNETWORK", "Qlackjack");   // If it is, load the save
        settings.setValue("wallpaperPath", filePath);   // Save the path to a custom wallpaper
        mw->changeWallpaper(filePath);  // Auto change the wallpaper in the main window
        wallpaperID = 0;    // Set the wallpaper ID to 0, meaning custom
    }
}

// When player wants random cards
void WallpaperSettings::on_random_clicked()
{
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    settings.setValue("cardBackID", 0); // Set the ID to 0, meaning random
    mw->initialise();   // Reinitialise game to update card's back
}

// When player wants to use a custom card
void WallpaperSettings::on_custom_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(    // Open a dialogue to let player choose a custom back card design
        this,
        "Choose a Card Back design",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );

    if (!filePath.isEmpty()) {  // If the path is valid
        QSettings settings("FFNETWORK", "Qlackjack");   // Load the save
        settings.setValue("cardBackPath", filePath);    // Set the custom back path to the one provided
        settings.setValue("cardBackID", 4); // Set the ID to 4, meaning custom
        mw->initialise();   // Reinitialise game to update card's back
    }
}

// When player chooses a blue card back
void WallpaperSettings::on_blueCard_clicked()
{
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    settings.setValue("cardBackID", 1); // Enforce blue design
    mw->initialise();   // Reinitialise game to update card's back
}

// When player chooses a green card back
void WallpaperSettings::on_greenCard_clicked()
{
    QSettings settings("FFNETWORK", "Qlackjack");    // Load save
    settings.setValue("cardBackID", 2); // Enforce green back design
    mw->initialise();   // Reinitialise game to update card's back
}

// When player chooses a red card back
void WallpaperSettings::on_redCard_clicked()
{
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the save
    settings.setValue("cardBackID", 3); // Enforce the red design
    mw->initialise();   // Reinitialise game to update card's back
}

