#include "wallpaperassistant.h"
#include "qsettings.h"

WallpaperAssistant::WallpaperAssistant(QWidget *parent) {
    parentWidget = parent;
}

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

void WallpaperAssistant::changeWallpaper(const QString &filePath) {
    // Load background image
    QPixmap bg(filePath);
    if (bg.isNull()) {  // If it fails to load
        qWarning() << "Failed to load wallpaper with from" << filePath;
        // currentWallpaperId = 2; // Set the default wallpaper to the second one if the file is missing
        return; // Quit function abruptly
    }

    // Scale it perfectly to current window size
    QPixmap scaled = bg.scaled(parentWidget->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaled); // Make the background scaled
    parentWidget->setPalette(palette);  // Set the background
    parentWidget->setAutoFillBackground(true);  // Ensure auto filling is on
}
