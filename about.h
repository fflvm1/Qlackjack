#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(MainWindow *w = nullptr);
    ~About();

private slots:
    void on_tabWidget_currentChanged(int index);    // Change tabs/windows

private:
    Ui::About *ui;
    MainWindow* mw; // Reference to main window
};

#endif // ABOUT_H
