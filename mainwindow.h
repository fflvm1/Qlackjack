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

private slots:
    void on_hit_clicked();  // Function that triggers upon player pressing the Hit button

    void on_stand_clicked();    // Function that triggers upon player pressing the Stand button

    void on_play_again_clicked();   // Function that triggers upon player pressing the Play Again button

private:
    Ui::MainWindow *ui; // The UI pointer
    Player p;   //  The player
    Dealer d;   // The dealer
    QLabel* secondCard = nullptr;   // Pointer to dealer's second card
    int secondCardValue = 0;    // Value of the second card
};
#endif // MAINWINDOW_H
