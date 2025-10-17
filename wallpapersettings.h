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

    void on_custom_bg_clicked();    // When player sets a custom background

    void on_random_clicked();   // When player chooses to set a random card back

    void on_custom_clicked();   // When player chooses to set a custon card back

    void on_blueCard_clicked(); // When the player chooses to set a blue card back

    void on_greenCard_clicked();    // When the player chooses to set a green card back

    void on_redCard_clicked();  // When player chooses to set a red card back

    void on_tabWidget_currentChanged(int index);    // Change tabs/windows

private:
    Ui::WallpaperSettings *ui;
    MainWindow *mw; // Reference to the main window
    int wallpaperID = 2;    // Selected wallpaper ID
    WallpaperAssistant *wa = new WallpaperAssistant(this);  // Wallpaper assistaint
};

#endif // WALLPAPERSETTINGS_H
