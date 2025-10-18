#ifndef WALLPAPERASSISTANT_H
#define WALLPAPERASSISTANT_H

#include <QWidget>

class WallpaperAssistant
{
public:
    WallpaperAssistant(QWidget *parent = nullptr);
    void changeWallpaper(int id);   // Changing wallpaper via ID
    void changeWallpaper(const QString &filePath);  // Setting custom wallpaper
    void loadWallpaperFromLastSave();   // Change the wallpaper based on the saved value
private:
    QWidget* parentWidget;  // Parent widget reference
};

#endif // WALLPAPERASSISTANT_H
