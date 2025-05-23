#include "MealScreen.h"
#include "ui_MealScreen.h"

MealScreen::MealScreen(QWidget* parent) : BasePumpScreen(parent, "Meal"), ui(new Ui::MealScreen) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
}

MealScreen::~MealScreen() {
    delete ui;
}

void MealScreen::newMealSlot() {
    double carbs = ui->doubleSpinBox->value();
    emit newMealSignal(carbs);
}

REGISTER_DERIVED_TYPE(MealScreen);
