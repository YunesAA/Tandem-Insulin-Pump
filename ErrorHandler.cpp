#include "ErrorHandler.h"
#include "ErrorDialog.h"

ErrorHandler::ErrorHandler(QObject* parent, DeliveryHistory* delivery_history): QObject(parent), delivery_history(delivery_history) {}

ErrorHandler::~ErrorHandler() {}

void ErrorHandler::handlePumpFailure() {
    DeliveryError* error = new DeliveryError(PUMP_FAILURE);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(PUMP_FAILURE);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void ErrorHandler::handlePowerFailure() {
    DeliveryError* error = new DeliveryError(POWER_FAILURE);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(POWER_FAILURE);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void ErrorHandler::handleLowBattery() {
    DeliveryError* error = new DeliveryError(LOW_BATTERY);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(LOW_BATTERY);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void ErrorHandler::handleLowInsulin() {
    if (lowInsulinShown) {
        return;
    }

    lowInsulinShown = true;
    DeliveryError* error = new DeliveryError(LOW_INSULIN);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(LOW_INSULIN);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(dialog, &QDialog::destroyed, [this]() {
        lowInsulinShown = false;
    });

    dialog->show();
}

void ErrorHandler::handleLowGlucose() {
    if (lowGlucoseShown) {
        return;
    }

    lowGlucoseShown = true;
    DeliveryError* error = new DeliveryError(LOW_GLUCOSE);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(LOW_GLUCOSE);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(dialog, &QDialog::destroyed, [this]() {
        lowGlucoseShown = false;
    });

    dialog->show();
}

void ErrorHandler::handleHighGlucose() {
    if (highGlucoseShown) {
        return;
    }

    highGlucoseShown = true;
    DeliveryError* error = new DeliveryError(HIGH_GLUCOSE);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(HIGH_GLUCOSE);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(dialog, &QDialog::destroyed, [this]() {
        highGlucoseShown = false;
    });

    dialog->show();
}

void ErrorHandler::handleNoInsulin() {
    if (noInsulinShown) {
        return;
    }

    noInsulinShown = true;
    DeliveryError* error = new DeliveryError(NO_INSULIN);
    delivery_history->addError(error);
    ErrorDialog* dialog = new ErrorDialog(NO_INSULIN);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(dialog, &QDialog::destroyed, [this]() {
        noInsulinShown = false;
    });

    dialog->show();
}
