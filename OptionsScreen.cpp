#include "OptionsScreen.h"
#include "ui_OptionsScreen.h"

OptionsScreen::OptionsScreen(QWidget* parent)
    : BasePumpScreen(parent, "Options"), ui(new Ui::OptionsScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

OptionsScreen::~OptionsScreen() {
    delete ui;
}

// Handles starting and stopping of insulin delivery. Only for emergencies.
void OptionsScreen::stopInsulin() {
    if (insulinIsBeingDelivered) {
        emit stopInsulinButtonClicked();
    } else {
        emit startInsulinButtonClicked();
    }
}

void OptionsScreen::onInsulinStopped() {
    insulinIsBeingDelivered = false;
    ui->stopInsulinButton->setText("Resume Insulin");
    ui->stopInsulinButton->setStyleSheet("color: green;");
}

void OptionsScreen::onInsulinResumed() {
    insulinIsBeingDelivered = true;
    ui->stopInsulinButton->setText("Stop Insulin");
    ui->stopInsulinButton->setStyleSheet("color: red;");
}

void OptionsScreen::navigateToProfiles() {
    emit profileButtonClicked();
}

void OptionsScreen::navigateToHistory() {
    emit historyButtonClicked();
}

REGISTER_DERIVED_TYPE(OptionsScreen);
