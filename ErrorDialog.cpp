#include "ErrorDialog.h"
#include "ui_ErrorDialog.h"

ErrorDialog::ErrorDialog(ErrorType error, QDialog *parent)
    : QDialog(parent), ui(new Ui::ErrorDialog) {
    ui->setupUi(this);
    displayError(error);
}

ErrorDialog::~ErrorDialog() {
    delete ui;
}

void ErrorDialog::displayError(ErrorType error) {
    QString message;

    switch (error) {
        case PUMP_FAILURE:
            message = "Pump failure detected.";
            break;

        case POWER_FAILURE:
            message = "Power failure.";
            break;

        case LOW_BATTERY:
            message = "Low battery. Please charge";
            break;

        case LOW_INSULIN:
            message = "Low insulin.";
            break;

        case LOW_GLUCOSE:
            message = "Low glucose.";
            break;

        case HIGH_GLUCOSE:
            message = "High glucose.";
            break;

        case NO_INSULIN:
            message = "No insulin. Refill insulin";
            break;
    }

    ui->error_text->setText(message);
}
