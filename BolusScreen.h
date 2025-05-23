//Provides interface for manual bolus entry and calculation.
#ifndef BOLUSSCREEN_H
#define BOLUSSCREEN_H
#include <QWidget>
#include "BolusCalculator.h"
#include "BasePumpScreen.h"

namespace Ui {
    class BolusScreen;
}

class BolusScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit BolusScreen(QWidget* parent = nullptr);
        ~BolusScreen();

    public slots:
        void displayBolusResult(double bolusDose);

    signals:
        void bolusAdministered();
        void signalBolusCalculator(double carbs, double bg, int hours, bool extended);
        void extendedBolusDeliverySignal(bool extended);
        void extendedHours(double hours);

    private slots:
        // void calculateDelayedBolus();
        // void calculateImmediateBolus();
        void calculateBolus(); //this doesnt work, but it should
        void confirmBolus();
        void setExtendedHours();

    private:
        Ui::BolusScreen* ui;
        BolusCalculator* bolusCalculator;
        double bg;
        double carbs;
        double hours;
        bool extended;
};

#endif // BOLUSSCREEN_H
