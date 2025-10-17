#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "player.h"
#include "drawcard.h"
#include "wallpaperassistant.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DrawCard *drawcard = new DrawCard(this);    // Reference to the DrawCard class

    void initialise();  // Initilisation function used to hide unnecessary UI features, give first two cards, etc.
    void checkState(bool isDealer, bool init);  // Function that checks if the game has to continue or if someone had already lost
    void dealerHit();   // Function used to send a signal to the dealer to try to hit
    void gameOver();    // Function used to set buttons like Play Again visible, and set buttons like Hit or Htand to be invisible
    void addPlayerCard(int value);  // Create a player card
    void addDealerCard(int value, bool isSecondCard = false);   // Create a dealer card
    void playSound(const QString &path);    // Function that plays sound via path
    void changeWallpaper(int id);   // Function that changes wallpaper
    void changeWallpaper(const QString &filePath);  // Change wallpaper to a custom one via path
    void loadStats();   // Loads player stats from QSettings
    void saveStats();   // Saves player stats to QSettings
    int aiMode = 0; // Selected AI preset
    QString playerName = "Player";  // Player's default name
    QString dealerName = "Dealer";  // Dealer's default name
    WallpaperAssistant *wa = new WallpaperAssistant(this);  // Wallpaper assistant

private slots:
    void on_hit_clicked();  // Function that triggers upon player pressing the Hit button

    void on_stand_clicked();    // Function that triggers upon player pressing the Stand button

    void on_play_again_clicked();   // Function that triggers upon player pressing the Play Again button

public slots:
    void on_tabWidget_currentChanged(int index);    // Change tabs/windows

private:
    Ui::MainWindow *ui; // The UI pointer
    Player p;   //  The player
    Dealer d;   // The dealer
    QPointer<QLabel> secondCard;   // Pointer to dealer's second card
    int secondCardValue = 0;    // Value of the second card
    bool isGameActive = false;  // Checks if the game is active(necessary to punish people for restarting the game in the middle)
    int wins = 0;   // Victories(to be imported from QSettings)
    int losses = 0; // Losses(to be imported from QSettings)
    int currentWallpaperId = 1; // Keep track of current background(via QSettings)
    bool enableSounds = true;   // Sound preferences from QSettings
    QString customWallpaperPath = "";   // Custom wallpaper path(if one is set)
    void giveCardsBeginning(int i);  // Gives the player and the dealer two cards at the beginning of the game
    bool enableStartGameButton = false; // Determines whether the Play Again button can show again or not
    bool isAnimationInProgress = false;   // Prevents constant reinitialisation of the game
protected:
};
#endif // MAINWINDOW_H
