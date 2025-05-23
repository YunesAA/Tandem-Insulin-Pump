#include "BolusScreen.h"
#include "BolusCalculator.h"
#include "ui_BolusScreen.h"

BolusScreen::BolusScreen(QWidget* parent): BasePumpScreen(parent, "bolus"),
    ui(new Ui::BolusScreen), bolusCalculator(new BolusCalculator(this)) {
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, buttonBar);
    connect(bolusCalculator, &BolusCalculator::bolusCalculatedDisplay, this, &BolusScreen::displayBolusResult);
    connect(this, &BolusScreen::extendedBolusDeliverySignal,
            bolusCalculator, &BolusCalculator::setExtendedBolusDelivery);
    connect(this, &BolusScreen::extendedHours,
            bolusCalculator, &BolusCalculator::setExtendedHours);///
}

BolusScreen::~BolusScreen() {
    delete ui;
}

void BolusScreen::calculateBolus() {
    carbs = ui->carbs_textEdit->toPlainText().toDouble();
    bg = ui->bg_textEdit->toPlainText().toDouble();
    hours = ui->spinBox->value();
    extended = ui->radioButton_2->isChecked();
    emit signalBolusCalculator(carbs, bg, hours, extended); ///
}

void BolusScreen::displayBolusResult(double dose) {
    ui->textBrowser_2->setText(QString("Recommended Dose: %1 units").arg(QString::number(dose, 'f', 2)));
}

void BolusScreen::confirmBolus() {
    QString text = ui->textBrowser_2->toPlainText();

    if (!text.isEmpty()) {
        emit bolusAdministered();
    }
}

void BolusScreen::setExtendedHours() {
    this->hours = hours;
    emit extendedHours(hours);
}

REGISTER_DERIVED_TYPE(BolusScreen);
