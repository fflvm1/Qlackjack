#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::About)
{
    this->setFixedSize(565, 210); // Lock current window size
    ui->setupUi(this);
    QString qtVersion = QT_VERSION_STR;
    ui->license->setText("Qt " + qtVersion+"\nThis application uses the Qt framework © The Qt Company Ltd.\n"
                                             "Qt is licensed under the GNU Lesser General Public License version "
                                             "3.\nSee https://www.qt.io/licensing/ for details.");  // Set the license info text
}

About::~About()
{
    delete ui;
}
