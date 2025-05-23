#include "BatteryIndicator.h"
#include "ui_BatteryIndicator.h"
//#include "PumpWindow.h"

BatteryIndicator::BatteryIndicator(QWidget* parent) : QWidget(parent),
    ui(new Ui::BatteryIndicator), batteryLevel(100) {
    ui->setupUi(this);
    updateDisplay(batteryLevel);
    batteryTimer = new QTimer(this);
    connect(batteryTimer, &QTimer::timeout, this, &BatteryIndicator::decreaseBattery);
    batteryTimer->start(5000); // every 5 seconds
}

BatteryIndicator::~BatteryIndicator() {
    delete ui;
}

void BatteryIndicator::setBatteryLevel(int level) {
    batteryLevel = level;
    updateDisplay(batteryLevel);
}

void BatteryIndicator::updateDisplay(int batteryLevel) {
    //qDebug() << "updateDisplay "<< batteryLevel;
    ui->batteryLevel->setText(QString("%1%").arg(batteryLevel));
}

void BatteryIndicator::setPowerOffAction(QAction* action) {
    powerOffAction = action;
}

void BatteryIndicator::decreaseBattery() {
    if (batteryLevel > 0) {
        batteryLevel--;
        updateDisplay(batteryLevel);

        if (batteryLevel == 20) {
            emit batteryLow();
        }
    } else {
        batteryTimer->stop();

        //turns off screen when battery level reaches 0
        if (powerOffAction) {
            powerOffAction->trigger();
        }
    }
}

void BatteryIndicator::chargeBattery() {
    qDebug() << "batteryLevel currently: " << batteryLevel;
    batteryTimer->stop();
    setBatteryLevel(100);
    batteryTimer->start();
}
