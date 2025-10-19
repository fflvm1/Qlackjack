#include "about.h"
#include "ui_about.h"

About::About(MainWindow* w)
    : QDialog(w)
    , ui(new Ui::About)
{
    ui->setupUi(this);
    this->showFullScreen(); // Ensure the app scales probably
    mw = w; // Main window reference
    WallpaperAssistant wa(this);
    QString qtVersion = QT_VERSION_STR; // Get the Qt version
    ui->license->setText("Qt " + qtVersion+"\nThis application uses the Qt framework © The Qt Company Ltd.\n"
                                     "Qt is licensed under the GNU Lesser General Public License version "
                                     "3.\nSee https://www.qt.io/licensing/ for details.");  // Set the license info text
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

