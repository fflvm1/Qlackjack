#include "wallpapersettings.h"
#include "ui_wallpapersettings.h"
#include <QtCore/qsettings.h>

WallpaperSettings::WallpaperSettings(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::WallpaperSettings)
{
    ui->setupUi(this);
    mw = w; // Save reference to main window
    this->setFixedSize(400, 171); // Lock current size
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    wallpaperID = settings.value("wallpaperID", 2).toInt(); // Set wallpaperID to match the currently set wallpaper
}

// When window is removed
WallpaperSettings::~WallpaperSettings()
{
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    settings.setValue("wallpaperID", wallpaperID);  // Change saves wallpaper ID to the variable
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

