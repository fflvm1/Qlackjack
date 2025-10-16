#include "mainwindow.h"
#include "about.h"
#include "settings.h"
#include "stats.h"
#include "ui_mainwindow.h"
#include "wallpapersettings.h"
#include "aimode.h"

#include <QTimer>
#include <QSoundEffect>
#include <QInputDialog>
#include <QSettings>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->playerDeck->setAlignment(Qt::AlignLeft);    // Ensures that cards appear on the left side of the player's deck
    ui->dealerDeck->setAlignment(Qt::AlignRight);   // Ensures that cards appear on the right side of the dealer's deck
    loadStats();    // Load save
    if (currentWallpaperId != 0) {  // Check if the saved wallpaper is NOT a custom one
        changeWallpaper(currentWallpaperId); // If it's not, show the last saved wallpaper or the default(second) wallpaper
    }   else {  // If it a custom one
            changeWallpaper(customWallpaperPath);   // Change the wallpaper to that path
        }
    ui->actionEnable_Sounds->setChecked(enableSounds);  // Make enableSounds checked/unchecked based on if the sounds were enabled during the save
    initialise();   // Initialise game
}

MainWindow::~MainWindow()
{
    // Give player a loss if they quit mid-game
    if (isGameActive) { // Check if the game is active
        losses++;   // If yes, increase losses
        saveStats();    // Save stats
    }

    delete ui;
}

// Initialisation function
void MainWindow::initialise() {
    ui->actionNew_Game->setEnabled(false);  // Make sure that the player can't start a new game till the end of the animation
    // Makes the Play Again button & the finish message invisible
    ui->play_again->setVisible(false);
    ui->finish_message->setVisible(false);
    // Ensure hit & stand animations are hidden till the end of the animation
    ui->hit->setVisible(false);
    ui->stand->setVisible(false);
    // Update labels
    ui->p_cards_text->setText(playerName + "'s cards: ");
    ui->p_hands_text->setText(playerName + "'s hands: ");
    ui->d_hands_text->setText(dealerName + "'s hands(approx.): "); /* Changes the dealer's hands text to reflect that the value is only approximate
    as after the game, it reflects the real value*/
    ui->d_cards_text->setText(dealerName + "'s cards: ");
    ui->statusBar->clearMessage();  // Clears the statusbar messages if there are any
    p.reset();  // Clears the player's cards array
    d.reset();  // Clears the dealer's cards array
    // Remove any cards present in player's and dealer's deck at the beginning of the game
    while (QLayoutItem* item = ui->playerDeck->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    while (QLayoutItem* item = ui->dealerDeck->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    playSound("qrc:/sfx/sound/place_cards.wav");    // Play the giving cards sound
    // Loop that adds two cards to the player & the dealer
    for (int i = 0; i < 2; i++) {
        QTimer::singleShot(i * 1000, this, [this, i]() {    // Timer
            giveCardsBeginning(i);
        });
    }
}

// When the Hit button is pressed
void MainWindow::on_hit_clicked()
{
    isGameActive = true;
    playSound("qrc:/sfx/sound/flipCard.wav");  // Play the hitting sound
    int hitValue = p.hit();    // Triggers player's hit function and stores the value of the hit
    addPlayerCard(hitValue);    // Adds a card corresponding to the value
    ui->statusBar->showMessage(playerName + " hits");  // The statusbar reflects player's action
    ui->player_hands->setText(QString::number(p.calculateHands())); // Changes player's total value text to match the one in the array
    ui->player_cards->setText(QString::number(p.calculateCards())); // Changes the player's card count to match the real count
    checkState(false, false);   // Checks whether the player had won with parameters: not a dealer, this is not the beginning of the game
}

// When the Stand button is pressed
void MainWindow::on_stand_clicked()
{
    isGameActive = true;
    playSound("qrc:/sfx/sound/stand.wav");  // Play the standing sound
    ui->hit->setVisible(false); // Sets the Hit button's visibility to invisible
    ui->stand->setVisible(false);   // Same for the Stand button
    ui->statusBar->showMessage(playerName + " stands");    // Changes the statusbar's message to reflect what just happened

    QTimer::singleShot(1500, this, [this]() {   // We wait for a second and a half to simulate the dealer thinking
        dealerHit();    // Dealer tries to hit/stand
    });
}

// Checking the game state(if anybody won/lost)
void MainWindow::checkState(bool isDealer, bool init) {
    if (isDealer) { // If this was triggered by the dealer
        if (d.calculateHands(true) == 21) { // We check if the dealer's total value is 21
                gameOver(); // If it is, hide the unnecessary, show the necessary
                ui->finish_message->setText(dealerName + " won!"); // Change the "action message" to reflect the dealer's victory
                ui->statusBar->showMessage(dealerName + " won. Better luck next time!");   // Change the status bar to reflect his victory
                playSound("qrc:/sfx/sound/lose.wav");   // Play the game over sound effect
                if (aiMode == 0) {  // If player is playing with the default AI preset
                    losses++;   // Increase losses
                    saveStats();    // Save stats
                }
                if (init)   // If dealer got 21 upon the game just starting
                    ui->finish_message->setText(dealerName + " BLACKJACK!");    // Change the action message to Dealer BLACKJACK!
        }   else if (d.calculateHands(true) > 21) { // If the dealer went out of bounds
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText(dealerName + " out of bounds.");   // Change the "action message" to reflect the dealer's loss
                ui->statusBar->showMessage("You won! Congratulations!");    // Chanhe the statusbar message to reflect player's victory
                playSound("qrc:/sfx/sound/victory.wav");    // Play the victory chime
                if (aiMode == 0) {  // If player is playing with the default AI preset
                    wins++; // Increase wins
                    saveStats();    // Save stats
                }
        }   else {  // If the dealer didn't lose but didn't win either and the game continues
                if (!init) {    // We check if this function was not triggered during the initialisation process
                    ui->hit->setVisible(true);  // Make the Hit button visible again
                    ui->stand->setVisible(true);    // Do the same for the Stand button
                }
        }
    }   else {  // If the function was triggered by the player
        if (p.calculateHands() == 21) { // If the player's total value is 21
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText(playerName + " won!"); // Change the "action message" to reflect player's victory
                ui->statusBar->showMessage("You won! Congratulations!");    // Change the statusbar message to reflect the same thing
                playSound("qrc:/sfx/sound/victory.wav");    // Play the victory chime
                if (aiMode == 0) {  // If player is playing with the default AI preset
                    wins++; // Increase wins
                    saveStats();    // Save stats
                }
                if (init)   // If player got 21 at the beginning of the game
                    ui->finish_message->setText(playerName + " BLACKJACK!");    // Change the action message to Player BLACKJACK!
        }   else if (p.calculateHands() > 21) { // If the player went out of bounds
                gameOver(); // Hide the unnecessary, show the necessary
                ui->finish_message->setText(playerName + " out of bounds.");   // We change the "action message"
                ui->statusBar->showMessage(dealerName + " won. Better luck next time!");   // Same thing with the statusbar
                playSound("qrc:/sfx/sound/lose.wav");   // Play the game over sound effect
                if (aiMode == 0) {  // If player is playing with the default AI preset
                    losses++;   // Increase losses
                    saveStats();    // Save stats
                }
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
    int hitValue = d.hit(aiMode); // Stores the dealer's hit value
    if (hitValue != 0) {  // Checks if the value is NOT set to 0.
        ui->statusBar->showMessage(dealerName + " hits");  // If it's not, dealer chose to hit and we update the statusbar message
        addDealerCard(hitValue);    // Add a card to the dealer's deck corresponding to the hit value
        playSound("qrc:/sfx/sound/flipCard.wav");   // Play the flipping card sound to indicate a hit
    }   else {  // If the value is set to 0
        ui->statusBar->showMessage(dealerName + " stands");    // The dealer chose to stand, update the statusbar message
        playSound("qrc:/sfx/sound/stand.wav");  // Play the putting card back sound to indicate a stand
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
    isGameActive = false;   // Set the game active status to false to prevent hitting new game counting as a loss
    ui->finish_message->setVisible(true);   // Shows the "action message"
    ui->hit->setVisible(false); // Hides the Hit button
    ui->stand->setVisible(false);   // Hides the Stand button
    ui->d_hands_text->setText(dealerName + "'s hands(actual): ");  // Updates the dealer's hands text to reflect that actual value has been revealed
    ui->dealer_hands->setText(QString::number(d.calculateHands(true))); // Reveal dealer's total value in hands
    QLabel* card = drawcard->createCard(secondCardValue, false);    // Create a replacement card with uncovered value
    ui->dealerDeck->replaceWidget(secondCard, card);    // Replace the covered card with an uncovered
    secondCard->deleteLater();  // Remove the covered version completely
    secondCard = nullptr;   // Clear the pointer

    QTimer::singleShot(1500, this, [this]() {   // Timer
        ui->play_again->setVisible(true);   // Shows the Play Again button
    });
}

// Add a card to the player's deck
void MainWindow::addPlayerCard(int value) {
    // We draw a card based on the value and the fact that it's not the dealer's second card
    QLabel* card = drawcard->createCard(value, false);
    ui->playerDeck->insertWidget(-1, card);  // Insert the widget to the playerdeck
}

// Add a card to dealer's deck
void MainWindow::addDealerCard(int value, bool isSecondCard) {
    QLabel* card = drawcard->createCard(value, isSecondCard);   // Draw a card with specified value and whether it's a second card or not
    ui->dealerDeck->insertWidget(0, card); // Insert it to the right side of the dealer's deck
    if (isSecondCard) { // If we're adding the second card
        secondCard = card;  // We save a pointer to it
        secondCardValue = value;    // We save it's value
    }
}

// Play sound via path
void MainWindow::playSound(const QString &path)
{
    if (enableSounds) { // Play sounds only if the player has them enabled
        QSoundEffect *effect = new QSoundEffect(this);  // Create a new sound effect
        effect->setSource(QUrl(path));  // Set the source to provided path
        effect->setVolume(0.8f);   // Set volume (from 0.0 to 1.0)
        effect->play(); // Play the following SFX

        // Delete when finished to prevent memory buildup
        connect(effect, &QSoundEffect::playingChanged, effect, [effect]() {
            if (!effect->isPlaying()) effect->deleteLater();
        });
    }
}

// Changing player's name
void MainWindow::on_actionChange_Player_s_Name_triggered()
{
    bool ok;
    QString newName = QInputDialog::getText(
        this,
        tr("Change Player Name"),   // Dialog name
        tr("Enter a new name for the Player:"), // Dialog title(inside of the window)
        QLineEdit::Normal,
        playerName,  // Default text
        &ok
        );

    if (ok && !newName.trimmed().isEmpty()) {   // Check if okay had been pressed and if the text isn't empty
        playerName = newName;   // Update the player name variable
        // Update the two labels
        ui->p_cards_text->setText(playerName + "'s cards: ");
        ui->p_hands_text->setText(playerName + "'s hands: ");
        saveStats();    // Save the player name
    }
}

// Changing dealer's name
void MainWindow::on_actionChange_Dealer_s_Name_triggered()
{
    bool ok;
    QString newName = QInputDialog::getText(
        this,
        tr("Change Dealer Name"),   // Dialog name
        tr("Enter a new name for the Dealer:"), // Dialog title(inside of the window)
        QLineEdit::Normal,
        dealerName,  // Default text
        &ok
        );

    if (ok && !newName.trimmed().isEmpty()) {   // Check if okay had been pressed and if the text isn't empty
        dealerName = newName;   // Update the dealer name variable
        // Update the two labels
        ui->d_cards_text->setText(dealerName + "'s cards: ");
        ui->d_hands_text->setText(dealerName + "'s hands(approx.): ");
        saveStats();    // Save the dealer name
    }
}

// When the New Game action is triggered
void MainWindow::on_actionNew_Game_triggered() {
    initialise();   // Reinitialise game

    if (isGameActive && aiMode == 0) { // If the game is active and the AI preset is the default one
        isGameActive = false;   // We make it inactive
        losses++;   // Count this as a loss
        saveStats();    // And save the stats
    }
}

// When the Change Wallpaper action is triggered
void MainWindow::on_actionChange_Wallpaper_triggered() {
    WallpaperSettings ws(this); // Create a WallpaperSettings window with a reference to the main window
    ws.exec();  // Ensure that it actually appears on the screen
}

// Change wallpaper function(for default wallpapers)
void MainWindow::changeWallpaper(int id)
{
    // Load background image
    QPixmap bg(":/backgrounds/assets/background_" + QString::number(id) + ".png");
    if (bg.isNull()) {  // If it fails to load
        qWarning() << "Failed to load wallpaper with ID" << id;
        return; // Quit function abruptly
    }

    // Scale it perfectly to current window size
    QPixmap scaled = bg.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaled); // Make the background scaled
    this->setPalette(palette);  // Set the background
    this->setAutoFillBackground(true);  // Ensure auto filling is on
}

// Change wallpaper to a custom one.
void MainWindow::changeWallpaper(const QString &filePath)
{
    // Load background image
    QPixmap bg(filePath);
    if (bg.isNull()) {  // If it fails to load
        qWarning() << "Failed to load wallpaper with from" << filePath;
        currentWallpaperId = 2; // Set the default wallpaper to the second one if the file is missing
        return; // Quit function abruptly
    }

    // Scale it perfectly to current window size
    QPixmap scaled = bg.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, scaled); // Make the background scaled
    this->setPalette(palette);  // Set the background
    this->setAutoFillBackground(true);  // Ensure auto filling is on
}

// When the player tries to resize the window
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // Reapply the wallpaper dynamically on every resize(to prevent tiling)
    if (currentWallpaperId != 0) {  // If the wallpaper is NOT custom
        changeWallpaper(currentWallpaperId);    // Set it based on the ID
    }   else {  // If it's custom
            changeWallpaper(customWallpaperPath);   // Set one from the provided path
    }
}

// When the player views stats
void MainWindow::on_actionView_Stats_triggered() {
    Stats s;    // Creates the stats window
    s.setStats(wins, losses);   // Sets the stats to match currently loaded stats

    connect(&s, &Stats::resetStatsRequested, this, [this, &s]() {   // If a reset it requested
        wins = 0;   // Sets the wins to 0
        losses = 0; // Same for losses
        saveStats();    // Save stats
        s.setStats(wins, losses);   // Set stats to match the newly updates stats
    });
    s.exec();   // Show the stats window
}

// Load stats
void MainWindow::loadStats() {
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the stats
    wins = settings.value("wins", 0).toInt();   // Convert the wins to an integer
    losses = settings.value("losses", 0).toInt();   // Convert the losses to an integer
    currentWallpaperId = settings.value("wallpaperID", 2).toInt();  // Get the current wallpaper
    playerName = settings.value("playerName", "Player").toString(); // Get the saved player name
    dealerName = settings.value("dealerName", "Dealer").toString(); // Get the saved dealer name
    enableSounds = settings.value("enableSounds", true).toBool();   // Check if the sound is enabled
    customWallpaperPath = settings.value("wallpaperPath", "").toString();   // Get the custom wallpaper location
    ui->p_cards_text->setText(playerName + "'s cards: ");
    ui->p_hands_text->setText(playerName + "'s hands: ");
    ui->d_hands_text->setText(dealerName + "'s hands(approx.): ");
    ui->d_cards_text->setText(dealerName + "'s cards: ");
}

// Save stats
void MainWindow::saveStats() {
    QSettings settings("FFNETWORK", "Qlackjack");   // Load the current stats
    settings.setValue("wins", wins);    // Set wins to match the wins variable
    settings.setValue("losses", losses);    // Set losses to match the losses variable
    settings.setValue("playerName", playerName);    // Save the player name
    settings.setValue("dealerName", dealerName);    // Save the dealer name
    settings.setValue("enableSounds", enableSounds);    // Save player's sound preferences
}

// Open AI presets window
void MainWindow::on_actionAI_Settings_triggered() {
    AiMode ai(this);    // Create the window with a reference to the main one
    ai.updateDefault(aiMode);   // Update the default selected mode to the one that is currently set
    ai.exec();  // Show the window
}

// Open About window
void MainWindow::on_actionAbout_triggered() {
    About a;    // Create the window
    a.exec();   // Show it
}

// Unified settings
void MainWindow::on_actionSettings_triggered() {
    Settings* s = new Settings(this);   // Creates the settings window with a reference to the main window
    s->updateDefault(aiMode);   // Updates the default selected AI preset based on what's actually selected
    s->exec();  // Shows the window
    delete s;   // Removes it afterwards(as it crashes upon regular deletion for some reason)
}

// Enabling/disabling sound via the action bar
void MainWindow::on_actionEnable_Sounds_toggled(bool checked) {
    if (checked) {  // If the action is ticked
        enableSounds = true;    // Enable sounds
        saveStats();    // Save the settings
    }   else {  // If the action is not ticked
        enableSounds = false;   // Disable sounds
        saveStats();    // Save the settings
    }
}

// Gives cards to the player and the dealer at the beginning of the game
void MainWindow::giveCardsBeginning(int i) {
    int playerHitValue = p.hit();    // Forces the player to hit and stores the hit value
    addPlayerCard(playerHitValue);  // Draws an image of the card on the player's side of the deck
    // Changes the value & cards count to reflect the changes in the array
    ui->player_hands->setText(QString::number(p.calculateHands()));
    ui->player_cards->setText(QString::number(p.calculateCards()));
    checkState(false, true);    // Checks if player had won/lost

    QTimer::singleShot(600, this, [this, i]() { // Timer
    int dealerHitValue = d.hit(0);    // Forces the dealer to hit
    if (i == 1) {   // If it's the second hit, hide the card
        addDealerCard(dealerHitValue, true);
        // Make the Hit and Stand buttons visible
        ui->hit->setVisible(true);
        ui->stand->setVisible(true);
        ui->actionNew_Game->setEnabled(true);   // Make it possible to start a new game again
    }   else {  // Otherwise don't
        addDealerCard(dealerHitValue);
    }
    // Changes the hands & cards count to reflect the changes in the array
    ui->dealer_hands->setText(QString::number(d.calculateHands(false)));
    ui->dealer_cards->setText(QString::number(d.calculateCards()));
    checkState(true, true); // Checks if the dealer had lost or won
    });
}
