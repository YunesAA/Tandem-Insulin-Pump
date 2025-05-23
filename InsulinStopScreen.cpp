#include "InsulinStopScreen.h"
#include "ui_InsulinStopScreen.h"

InsulinStopScreen::InsulinStopScreen(QWidget* parent) : BasePumpScreen(parent, "Stop Insulin")
    , ui(new Ui::InsulinStopScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

InsulinStopScreen::~InsulinStopScreen() {
    delete ui;
}

void InsulinStopScreen::insulinStopConfirmedClicked() {
    // We need to get the time value the user will input inside the box called "RemindUserAfter"
    setTimer(ui->alarmMinutes->value());
    emit insulinStopConfirmed();
}

void InsulinStopScreen::setTimer(int time) {
    this->timer = time;
}

int InsulinStopScreen::getTimer() const {
    return this->timer;
}

void InsulinStopScreen::subtractOneMinuteFromTimer() {
    this->timer = timer - 1;
    emit timerUpdated();
}

REGISTER_DERIVED_TYPE(InsulinStopScreen);
