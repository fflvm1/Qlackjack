#include "drawcard.h"
#include <QtCore/qsettings.h>

DrawCard::DrawCard(QWidget* parent) {
    parentWidget = parent;  // Gets a pointer to the main window
}

// Returns a random suit string
QString DrawCard::randomSuit() const
{
    static const QStringList suits = {"clubs", "diamonds", "hearts", "spades"}; // Names array(which come from resources.qrc)
    int index = QRandomGenerator::global()->bounded(suits.size());  // Random index from the array
    return suits[index];    // Return the final string
}

// Map numeric value, filename suffix (A, 2–10, J, Q, K)
QString DrawCard::valueToName(int value) const
{
    switch (value) {
    case 1: // Checks if the value is 1
        return "A"; // If yes, then return the A card
    case 11:    // If the value is 11
    {
        static const QStringList faces = {"J", "Q", "K"};   // Array of cards that serve the value of 11
        int index = QRandomGenerator::global()->bounded(faces.size());  // A random index from that array
        return faces[index];    // The chosen card
    }
    default:    // If it's not 1 or 11
        return QString::number(value);  // We jusr return the value as a string
    }
}

// Create the card QLabel
QLabel* DrawCard::createCard(int value, bool isDealersSecondCard)
{
    QString suit = randomSuit();    // Random suit
    QString cardName = valueToName(value);  // Card name(value to name)
    QString path;   // Path to the image

    // Build the resource path (e.g. :/hearts/assets/cardHearts_10.png)
    if (!isDealersSecondCard) { // If this isn't dealer's second card
        path = QString(":/%1/assets/card%2_%3.png") // Placeholder path
                       .arg(suit)   // First argument is the random suit(e.g. "hearts")
                       .arg(suit.left(1).toUpper() + suit.mid(1))  // Converts it to match the format, e.g. "Hearts"
                       .arg(cardName);  // The number at the end(e.g. 2, Q)
    }   else {  // If it is the second card
            QSettings settings("FFNETWORK", "Qlackjack");   // Load save
            int backID = settings.value("cardBackID", 0).toInt();   // Check the chosen by player card in customisation settings
            switch(backID) {
                case 0:{    // If it's set to random
                    QString backColor = randomBackColour(); // Choose a random back colour
                    path = QString(":/card_back/assets/cardBack%1.png").arg(backColor); // Construct a proper path
                    break;
                }
                case 1:{    // If it's a blue card
                    path = QString(":/card_back/assets/cardBackBlue.png");  // Make the back always blue
                    break;
                }
                case 2:{    // If it's the green card
                    path = QString(":/card_back/assets/cardBackGreen.png"); // Make the back always green
                    break;
                }
                case 3:{    // If it's a red card
                    path = QString(":/card_back/assets/cardBackRed.png");   // Make the back always red
                    break;
                }
                case 4:{    // If it's a custom card
                    path = settings.value("cardBackPath", "").toString();   // Get path to that image
                    if (QPixmap(path).isNull()) {   // Check if the custom back exists before actually setting it
                        qWarning() << "User entered an invalid card back path! Reverting to a different image...";  // If not, pring a warning
                        path = QString(":/card_back/assets/cardBackRed.png");   // And revert the path to a normal back that actually exists
                    }
                    break;
                }
            }
    }

    QPixmap pixmap(path);   // Use the image's path to create a pixmap
    if (pixmap.isNull()) {  // If the path is incorrect because of a wrong path/missing file
        qWarning() << "Failed to load card asset:" << path; // We show a warning
    }

    QLabel* card = new QLabel(parentWidget);    // Create a card
    card->setFixedSize(60, 90); // Set it's size to 60x90
    card->setScaledContents(true);  // Set scaledContents to true so that the image matches the following size correctly
    card->setPixmap(pixmap);    // Set the picture via the pixmap created earlier

    return card;    // Return the card(to actually show it in the main window later)
}

// Random back colour
QString DrawCard::randomBackColour() const {
    QStringList colors = {"Blue", "Green", "Red"};  // Array of possible colour names
    int randomIndex = QRandomGenerator::global()->bounded(colors.size());   // Gets a random index
    return colors[randomIndex]; // Returns the colour based on the index
}
