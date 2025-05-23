#include "InsulinStartScreen.h"
#include "ui_InsulinStartScreen.h"

InsulinStartScreen::InsulinStartScreen(QWidget* parent) : BasePumpScreen(parent, "Start Insulin"),
    ui(new Ui::InsulinStartScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

InsulinStartScreen::~InsulinStartScreen() {
    delete ui;
}

void InsulinStartScreen::insulinStartConfirmedClicked() {
    emit insulinStartConfirmed();
}

REGISTER_DERIVED_TYPE(InsulinStartScreen);
