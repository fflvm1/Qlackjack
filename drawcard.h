#ifndef DRAWCARD_H
#define DRAWCARD_H

#include <QtWidgets/qwidget.h>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QRandomGenerator>

class DrawCard
{
public:
    explicit DrawCard(QWidget* parent = nullptr);

    QLabel* createCard(int value, bool isDealersSecondCard);    // Create card function triggered from the main window
private:
    QWidget* parentWidget;  // Parent widget(main window)
    QString randomSuit() const; // Random suit(E.g. diamonds, clubs and shite like that)
    QString valueToName(int value) const;   // Converts the value to filename
    QString randomBackColour() const;   // Random back colour(Green, Blue, Red, etc. If i add anything else)
};

#endif // DRAWCARD_H
