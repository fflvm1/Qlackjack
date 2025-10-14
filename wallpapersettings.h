#ifndef WALLPAPERSETTINGS_H
#define WALLPAPERSETTINGS_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class WallpaperSettings;
}

class WallpaperSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WallpaperSettings(MainWindow *w = nullptr);
    ~WallpaperSettings();

private slots:
    void on_bg1_clicked();  // When the player selects the first background

    void on_bg2_clicked();  // When the player selects the second background

    void on_bg_3_clicked(); // When the player selects the third background

private:
    Ui::WallpaperSettings *ui;
    MainWindow *mw; // Reference to the main window
};

#endif // WALLPAPERSETTINGS_H
