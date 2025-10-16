#ifndef AIMODE_H
#define AIMODE_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class AiMode;
}

class AiMode : public QDialog
{
    Q_OBJECT

public:
    explicit AiMode(MainWindow* w = nullptr);
    ~AiMode();

    void updateDefault(int index);  // Update selected preset in the listView

private:
    Ui::AiMode *ui;
    MainWindow* mw; // Reference to the main window
    int defaultAiMode;  // Original AI mode(before modifications)
};

#endif // AIMODE_H
