#include "wallpaperassistant.h"
#include "qsettings.h"

WallpaperAssistant::WallpaperAssistant(QWidget *parent) {
    parentWidget = parent;
    loadWallpaperFromLastSave();    // Automatically load the last wallpaper from a save
}

// Changing wallpaper via ID(those that are in the game)
void WallpaperAssistant::changeWallpaper(int id) {
    // Load background image
    QPixmap bg(":/backgrounds/assets/background_" + QString::number(id) + ".png");
    if (bg.isNull()) {  // If it fails to load
        qWarning() << "Failed to load wallpaper with ID" << id;
        return; // Quit function abruptly
    }

    // Scale it perfectly to current window size
    QPixmap scaled = bg.scaled(parentWidget->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaled); // Make the background scaled
    parentWidget->setPalette(palette);  // Set the background
    parentWidget->setAutoFillBackground(true);  // Ensure auto filling is on
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the save
    settings.setValue("wallpaperID", id);   // Save the updated wallpaper ID
}

// Changing wallpaper via path(custom wallpapers)
void WallpaperAssistant::changeWallpaper(const QString &filePath) {
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the save
    // Load background image
    QPixmap bg(filePath);
    if (bg.isNull()) {  // If it fails to load
        qWarning() << "Failed to load wallpaper with from" << filePath;
        settings.setValue("wallpaperID", 2); // Set the default wallpaper to the second one if the file is missing or it fails to load
        loadWallpaperFromLastSave();    // Reload the wallpaper(now as the second one)
        return; // Quit function abruptly
    }

    // Scale it perfectly to current window size
    QPixmap scaled = bg.scaled(parentWidget->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaled); // Make the background scaled
    parentWidget->setPalette(palette);  // Set the background
    parentWidget->setAutoFillBackground(true);  // Ensure auto filling is on
    settings.setValue("wallpaperID", 0);    // Update the saved wallpaper ID
}

// Load the wallpaper from the save
void WallpaperAssistant::loadWallpaperFromLastSave() {
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the save
    int currentWallpaperID = settings.value("wallpaperID", 2).toInt();  // Get the currently set ID from that save
    if (currentWallpaperID != 0) {  // If it's not 0(meaning not custom)
        changeWallpaper(currentWallpaperID);    // Change the wallpaper based on the ID
    }   else {  // If it custom get
        QString wallpaperPath = settings.value("wallpaperPath", "").toString(); // Get the path
        changeWallpaper(wallpaperPath); // Try changing wallpaper
    }
}
