#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>

// Player logic
class Player
{
public:
    int hit(); // Hitting
    void reset();   // Resetting cards if player chooses to play again
    int calculateHands();   // Calculates hands
    int calculateCards();   // Calculates cards
private:
    QVector<int> cards; // Array that stores values of cards
};

// Dealer logic
class Dealer
{
public:
    int hit(int mode); // Dealer's AI
    void reset();   // Resetting cards if player chooses to play again
    int calculateHands(bool actualValue);   // Calculates hands
    int calculateCards();   // Calculates cards
private:
    QVector<int> cards; // Array that stores values of cards
};

#endif // PLAYER_H
