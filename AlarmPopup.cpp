#include "AlarmPopup.h"
#include "BasePumpScreen.h"
#include "ui_AlarmPopup.h"

AlarmPopup::AlarmPopup(QWidget* parent) : BasePumpScreen(true), ui(new Ui::AlarmPopup) {
    ui->setupUi(this);
    ui->verticalLayout->addWidget(buttonBar);
}

AlarmPopup::~AlarmPopup() {
    delete ui;
}

REGISTER_DERIVED_TYPE(AlarmPopup);
