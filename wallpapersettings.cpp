#include "wallpapersettings.h"
#include "ui_wallpapersettings.h"

WallpaperSettings::WallpaperSettings(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::WallpaperSettings)
{
    ui->setupUi(this);
    mw = w; // Save reference to main window
    this->setFixedSize(400, 171); // Lock current size
}

WallpaperSettings::~WallpaperSettings()
{
    delete ui;
}

// When first background is chosen
void WallpaperSettings::on_bg1_clicked()
{
    mw->changeWallpaper(1); // Set the background to the first one
}

// When second background is chosen
void WallpaperSettings::on_bg2_clicked()
{
    mw->changeWallpaper(2); // Set the background to the second one
}

// When third background is chosen
void WallpaperSettings::on_bg_3_clicked()
{
    mw->changeWallpaper(3); // Set the background to the third one
}

