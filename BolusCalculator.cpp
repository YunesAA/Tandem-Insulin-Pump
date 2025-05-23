#include "BolusCalculator.h"
#include "InsulinPump.h"

BolusCalculator::BolusCalculator(QObject* parent): QObject(parent), recommendedDose(0.0),
    extendedBolusDelivery(false), delayTime(0) {}

void BolusCalculator::displayRecommendedDose(double dose) {
    emit bolusCalculatedDisplay(dose);
}

void BolusCalculator::setExtendedBolusDelivery(bool extended) {
    extendedBolusDelivery = extended;
    qDebug() << "BolusCalculator::setExtendedBolusDelivery: " << extendedBolusDelivery;
}

void BolusCalculator::setExtendedHours(int hours) {
    delayTime = hours;
    qDebug() << "BolusCalculator::setExtendedHours: " << delayTime;
}

void BolusCalculator::calculateBolus(double carbIntake, double currentBG, int hours, bool extended) {
    InsulinPump* pump = qobject_cast<InsulinPump*>(parent());
    pump->getActiveProfile();

    qDebug() << "carbIntake: " << carbIntake;
    qDebug() << "currentBG: " << currentBG;
    qDebug() << "extended: " << extended;

    ICR = 1.0 / 10.0;  // 1 unit per 10g of carbs
    CF = 1.0 / 1.0;    // 1 unit per 1 mmol/L
    targetBG = 5.0;
    IOB = 5.0;         // Insulin on board (IOB) in units
    // ==========BOLUS CALCULATION==========
    carbBolus = carbIntake / ICR;
    correctionBolus = (currentBG - targetBG) / CF;
    totalBolus = carbBolus + correctionBolus;
    finalBolus = totalBolus - IOB;

    extendedBolusDelivery = extended;
    delayTime = hours;

    if (extendedBolusDelivery) {
        //calculate the extended bolus
        immediateBolus = finalBolus * 0.6; // 60% immediate, 40% delayed
        QDateTime* time = new QDateTime(QDateTime::currentDateTime());
        qDebug() << "Immediate bolus delivered: " << immediateBolus << " units";

        //calculate the delayed bolus
        extendedBolus = finalBolus * 0.4; // 40% delayed
        qDebug() << "hours: " << delayTime;
        qDebug() << "extendedBolus = finalBolus*0.4: " << extendedBolus << "= " << finalBolus << "*0.4";
        qDebug() << "Immediate Insulin Dose: " << immediateBolus << " units at meal time";
        qDebug() << "Extended Insulin Delivery (extendedBolus/delayTime): " << extendedBolus / delayTime << " units per hour for" << delayTime << " hour(s)";


        emit bolusCalculatedImmediate(immediateBolus, *time);
        emit bolusCalculatedExtended((extendedBolus/delayTime), *time, delayTime);


    } else {
        //Immediate
        QDateTime* time = new QDateTime(QDateTime::currentDateTime());
        immediateBolus = finalBolus;

        emit bolusCalculatedImmediate(immediateBolus, *time);

        qDebug() << "Immediate Insulin Dose: " << immediateBolus << " units at meal time";
    }

    qDebug() << "Total insulin administered: " << finalBolus << " units";
    displayRecommendedDose(finalBolus);
}
