#include "about.h"
#include "qsettings.h"
#include "ui_about.h"

About::About(MainWindow* w)
    : QDialog(w)
    , ui(new Ui::About)
{
    ui->setupUi(this);
    this->showFullScreen(); // Ensure the app scales probably
    mw = w; // Main window reference
    WallpaperAssistant wa(this);
    QSettings settings("FFNETWORK", "Qlackjack");   // Load save
    int wallpaperID = settings.value("wallpaperID", 2).toInt(); // Set wallpaperID to match the currently set wallpaper
    wa.changeWallpaper(wallpaperID);    // Change the about menu wallpaper
}

About::~About()
{
    delete ui;
}

// If player switches tabs/windows
void About::on_tabWidget_currentChanged(int index)
{
    mw->on_tabWidget_currentChanged(index); // Open the next window(from main window)
    this->close();  // Close this window
}

