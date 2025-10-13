#include "player.h"

#include <QRandomGenerator>
#include <qDebug>

// Player: Hitting logic
int Player::hit() {
    int newCardValue = QRandomGenerator::global()->bounded(1, 12);
    cards.push_back(newCardValue);
    return newCardValue;
}

// Player: Calculating the amount of cards
int Player::calculateCards() {
    return cards.size();    // Calculates the amount of cards in the array
}

// Player: Calculating hands
int Player::calculateHands() {
    int totalHands = 0; // Total value

    // A loop that goes through each card
    for (int i = 0; i < cards.size(); i++) {
            totalHands += cards[i]; // Adds the current card's value to the total
    }

    return totalHands;  // Returns the total value
}

// Player: Resetting
void Player::reset() {
    cards.clear();  // Clears every entry of the array
}

// Dealer: Hitting logic
int Dealer::hit() {
    if (calculateHands(true) < 17) {    // Checks if the total value of all cards is less than 17
        int newCardValue = QRandomGenerator::global()->bounded(1, 12);    // If so, dealer hits
        cards.push_back(newCardValue);
        return newCardValue;
    }
    return 0;   // Otherwise, dealer stands
}

// Dealer: Calculating cards
int Dealer::calculateCards() {
    return cards.size();    // Calculates the amount of cards in the array
}

// Dealer: Calculating hands
int Dealer::calculateHands(bool actualValue) {
    int totalHands = 0; // The total value

    for (int i = 0; i < cards.size(); i++) {    // Runs through each card in the array
        if (i != 1 || actualValue) {    /* Doesn't index the second card unless actualValue is set to true.
            This is in accordance to Blackjack's rules, as it's forbidden to show the dealer's second card until the end of the game.*/
            totalHands += cards[i]; // Adds the current card to the array
        }
    }

    return totalHands;  // Returns the total value
}

// Dealer: Resetting
void Dealer::reset() {
    cards.clear();  // Clears the array
}
