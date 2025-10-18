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

