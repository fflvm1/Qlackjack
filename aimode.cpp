#include "aimode.h"
#include "ui_aimode.h"

AiMode::AiMode(MainWindow *w)
    : QDialog(w)
    , ui(new Ui::AiMode)
{
    mw = w; // Set mw to the reference to main window from constructor
    this->setFixedSize(400, 300); // Lock current size
    ui->setupUi(this);
    defaultAiMode = mw->aiMode; // Remember the AI mode used before any changes
}

AiMode::~AiMode()
{
    mw->aiMode = ui->listWidget->currentRow();  // Set the AI mode to match the selected mode
    if (defaultAiMode != ui->listWidget->currentRow()) {
        mw->initialise();   // Only reinitisialise the game if AI preset has been changed
    }

    delete ui;
}

// Update default selection to match the current selected mode
void AiMode::updateDefault(int index) {
    ui->listWidget->setCurrentRow(index);   // Set the selected row to int aiMode
}
