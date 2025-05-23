#include "InsulinReservoir.h"

// The insulin pump will contain 200 units of insulin as a start and full capacity
InsulinReservoir::InsulinReservoir() : level(200) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &InsulinReservoir::deliverExtendedBolus);
}

void InsulinReservoir::setLevel(float newLevel) {
    if (this->level != newLevel) {
        this->level = newLevel;
        emit levelChanged(newLevel);  // Emit signal only if there's a change
    }

    if(level <= 20 ){
        emit lowInsulin();
    }
}

float InsulinReservoir::getLevel() const {
    return this->level;
}

void InsulinReservoir::bolusImmediateSlot(double dose, QDateTime& time) {
    double new_level = level;
    qDebug() << "Bolus dose: " << dose;
    qDebug() << "Current reservoir level: " << level;

    if (dose < level) { // good
        new_level = level - dose;

        this->level = new_level;
        emit levelChanged(new_level);
        emit addDeliveryHistory(dose, time);

    } else { //bad
        qDebug() << "bolus dose exceeds reservoir level";
        emit addDeliveryHistory(0, time);
        emit noInsulinSignal();
        //handle error...
    }

}

void InsulinReservoir::bolusExtendedSlot(double dose, QDateTime& time, double delayTime) {
    timer->start(12000);

    for (int i = 0; i < delayTime; i++) {
        extendedDoses.append({dose, time, i + 1});
    }
}

void InsulinReservoir::deliverExtendedBolus() {
    if (extendedDoses.empty()) {
        timer->stop();
        return;
    } else {
        ScheduledDose current_dose = extendedDoses.takeFirst();
        QDateTime* time = new QDateTime(QDateTime::currentDateTime().addSecs(current_dose.position * 60 * 60));
        double new_level = level;

        if (current_dose.dose < level) {
            new_level = level - current_dose.dose;
        }

        this->level = new_level;
        emit levelChanged(level);
        emit addDeliveryHistory(current_dose.dose, *time);
    }
}

void InsulinReservoir::exerciseInsulinReduction(double intensity) {
    if (intensity == 1.0) {
        this->extendedDoses.first().dose = this->extendedDoses.first().dose - 3;
    } else if (intensity == 2.0) {
        this->extendedDoses.first().dose = this->extendedDoses.first().dose - 7;
    } else {
        this->extendedDoses.first().dose = this->extendedDoses.first().dose - 10;
    }
}
