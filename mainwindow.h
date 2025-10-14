#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "player.h"
#include "drawcard.h"

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
    void addPlayerCard(int value);
    void addDealerCard(int value, bool isSecondCard = false);
    void playSound(const QString &path);    // Function that plays sound via path
    void changeWallpaper(int id);   // Function that changes wallpaper
    void loadStats();   // Loads player stats from QSettings
    void saveStats();   // Saves player stats to QSettings
    int aiMode = 0; // Selected AI preset

private slots:
    void on_hit_clicked();  // Function that triggers upon player pressing the Hit button

    void on_stand_clicked();    // Function that triggers upon player pressing the Stand button

    void on_play_again_clicked();   // Function that triggers upon player pressing the Play Again button

    void on_actionChange_Player_s_Name_triggered(); // Event that triggers after player clicks Players -> Change Player's Name

    void on_actionChange_Dealer_s_Name_triggered(); // Event that triggers after player clicks Players -> Change Dealer's Name

    void on_actionNew_Game_triggered(); // Event that triggers after player clicks Game -> New Game

    void on_actionChange_Wallpaper_triggered(); // Event that triggers after player clicks Game -> Change Wallpaper

    void on_actionView_Stats_triggered();   // Event that triggers after player presses Game -> View Stats

    void on_actionAI_Settings_triggered();  // Event that triggers after player presses Players -> AI Settings

    void on_actionAbout_triggered();    // Event that triggers after player presses Help(or app name on Mac) -> About

private:
    Ui::MainWindow *ui; // The UI pointer
    Player p;   //  The player
    Dealer d;   // The dealer
    QLabel* secondCard = nullptr;   // Pointer to dealer's second card
    int secondCardValue = 0;    // Value of the second card
    QString playerName = "Player";  // Player's default name
    QString dealerName = "Dealer";  // Dealer's default name
    bool isGameActive = false;  // Checks if the game is active(necessary to punish people for restarting the game in the middle)
    int wins = 0;   // Victories(to be imported from QSettings)
    int losses = 0; // Losses(to be imported from QSettings)

protected:
    void resizeEvent(QResizeEvent *event) override; // Function that triggers upon resizing the window(to fit the background without tiling)
    void closeEvent(QCloseEvent *event) override;   // Function that triggers upon closing the window(supposed to prevent quitting without losing)
};
#endif // MAINWINDOW_H
