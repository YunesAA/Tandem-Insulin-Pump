#ifndef BOLUSCALCULATORVIEW_H
#define BOLUSCALCULATORVIEW_H
#include <QDebug>
#include <QObject>
#include <QDateTime>
#include "InsulinReservoir.h"

class BolusCalculator : public QObject {
        Q_OBJECT

    public:
        explicit BolusCalculator(QObject* parent = nullptr);

    public slots:
        void displayRecommendedDose(double dose);
        void calculateBolus(double carbIntake, double currentBG, int hours, bool extended);
        void setExtendedBolusDelivery(bool extended);
        void setExtendedHours(int hours);

    signals:
        void bolusCalculatedImmediate(double bolusDose, QDateTime& time);
        void bolusCalculatedExtended(double bolusDose, QDateTime& time, double delayTime);
        void bolusCalculatedDisplay(double dose);
        void bolusCalculated(double bolusDose, QDateTime& time);

    private:
        double recommendedDose;
        bool extendedBolusDelivery;
        double immediateBolus;
        double extendedBolus;
        int delayTime;
        double ICR;
        double CF;
        double targetBG;
        double currentBG;
        double IOB;
        double carbBolus;
        double correctionBolus;
        double totalBolus;
        double finalBolus;
};

#endif // BOLUSCALCULATORVIEW_H
