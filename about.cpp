#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    this->setFixedSize(434, 152); // Lock current size
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
