#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialise();   // Initialise game
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Initialisation function
void MainWindow::initialise() {
    // Makes the Play Again button & the finish message invisible
    ui->play_again->setVisible(false);
    ui->finish_message->setVisible(false);
    // Makes the Hit and Stand buttons visible
    ui->hit->setVisible(true);
    ui->stand->setVisible(true);
    ui->d_hands_text->setText("Dealer's hands(approx.): "); /* Changes the dealer's hands text to reflect that the value is only approximate
    as after the game, it reflects the real value*/
    ui->statusBar->clearMessage();  // Clears the statusbar messages if there are any
    p.reset();  // Clears the player's cards array
    d.reset();  // Clears the dealer's cards array

    // Loop that adds two cards to the player & the dealer
    for (int i = 0; i < 2; i++) {
        p.hit();    // Forces the player to hit
        // Changes the hands & cards count to reflect the changes in the array
        ui->player_hands->setText(QString::number(p.calculateHands()));
        ui->player_cards->setText(QString::number(p.calculateCards()));
        checkState(false, true);    // Checks if player had won/lost

        d.hit();    // Forces the dealer to hit
        // Changes the hands & cards count to reflect the changes in the array
        ui->dealer_hands->setText(QString::number(d.calculateHands(false)));
        ui->dealer_cards->setText(QString::number(d.calculateCards()));
        checkState(true, true); // Checks if the dealer had lost or won
    }
}

// When the Hit button is pressed
void MainWindow::on_hit_clicked()
{
    p.hit();    // Triggers player's hit function
    ui->statusBar->showMessage("Player hits");  // The statusbar reflects player's action
    ui->player_hands->setText(QString::number(p.calculateHands())); // Changes player's total value text to match the one in the array
    ui->player_cards->setText(QString::number(p.calculateCards())); // Changes the player's card count to match the real count
    checkState(false, false);   // Checks whether the player had won with parameters: not a dealer, this is not the beginning of the game
}

// When the Stand button is pressed
void MainWindow::on_stand_clicked()
{
    ui->hit->setVisible(false); // Sets the Hit button's visibility to invisible
    ui->stand->setVisible(false);   // Same for the Stand button
    ui->statusBar->showMessage("Player stands");    // Changes the statusbar's message to reflect what just happened

    QTimer::singleShot(1500, this, [this]() {   // We wait for a second and a half to simulate the dealer thinking
        dealerHit();    // Dealer tries to hit/stand
    });
}

// Checking the game state(if anybody won/lost)
void MainWindow::checkState(bool isDealer, bool init) {
    if (isDealer) { // If this was triggered by the dealer
        if (d.calculateHands(true) == 21) { // We check if the dealer's total value is 21
                gameOver(); // If it is, hide the unnecessary, show the necessary
                ui->finish_message->setText("Dealer won!"); // Change the "action message" to reflect the dealer's victory
                ui->statusBar->showMessage("Dealer won. Better luck next time!");   // Change the status bar to reflect his victory
        }   else if (d.calculateHands(true) > 21) { // If the dealer went out of bounds
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText("Dealer out of bounds.");   // Change the "action message" to reflect the dealer's loss
                ui->statusBar->showMessage("You won! Congratulations!");    // Chanhe the statusbar message to reflect player's victory
        }   else {  // If the dealer didn't lose but didn't win either and the game continues
                if (!init) {    // We check if this function was not triggered during the initialisation process
                    ui->hit->setVisible(true);  // Make the Hit button visible again
                    ui->stand->setVisible(true);    // Do the same for the Stand button
                }
        }
    }   else {  // If the function was triggered by the player
        if (p.calculateHands() == 21) { // If the player's total value is 21
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText("Player won!"); // Change the "action message" to reflect player's victory
                ui->statusBar->showMessage("You won! Congratulations!");    // Change the statusbar message to reflect the same thing
        }   else if (p.calculateHands() > 21) { // If the player went out of bounds
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText("Player out of bounds.");   // We change the "action message"
                ui->statusBar->showMessage("Dealer won. Better luck next time!");   // Same thing with the statusbar
        }   else {  // If the player didn't win or lose
                if (!init) {    // We check if the function wasn't triggered during the initialisation process
                    ui->hit->setVisible(false); // Hide the Hit button
                    ui->stand->setVisible(false);   // Same thing with the stand button

                    QTimer::singleShot(1500, this, [this]() {   // Timer to fake dealer's thinking
                    dealerHit();    // Dealer tries to hit or stand
                    });
                }
        }
    }
}

// Dealer's hitting/standing logic
void MainWindow::dealerHit() {
    if (d.hit()) {  // Triggers the hit() function and checks whether the AI chose to hit or stand
        ui->statusBar->showMessage("Dealer hits");  // If it chose to hit, reflect that in the statusbar
    }   else {  // If it chose to stand
        ui->statusBar->showMessage("Dealer stands");    // Reflect that in the statusbar instead
    }

    ui->dealer_hands->setText(QString::number(d.calculateHands(false)));    // Update the total value without revealing the second card
    ui->dealer_cards->setText(QString::number(d.calculateCards())); // Update the amount of cards the dealer has
    checkState(true, false);    // Check if the dealer had won/lost
}

// Play Again button logic
void MainWindow::on_play_again_clicked()
{
    initialise();   // Just reinitialises the game
}

// The hiding unnecessary & showing the necessary function, or whatever name that i gave it
void MainWindow::gameOver() {
    ui->finish_message->setVisible(true);   // Shows the "action message"
    ui->play_again->setVisible(true);   // Shows the Play Again button
    ui->hit->setVisible(false); // Hides the Hit button
    ui->stand->setVisible(false);   // Hides the Stand button
    ui->d_hands_text->setText("Dealer's hands(actual): ");  // Updates the dealer's hands text to reflect that actual value has been revealed
    ui->dealer_hands->setText(QString::number(d.calculateHands(true))); // Reveal dealer's total value in hands
}
