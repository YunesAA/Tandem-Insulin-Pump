// Error handler class that handles malfunctions, generates alerts, and logs errors.
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "DeliveryHistory.h"
#include <QObject>

class ErrorHandler : public QObject {
        Q_OBJECT

    public:
        explicit ErrorHandler(QObject* parent = nullptr, DeliveryHistory* delivery_history = nullptr);
        ~ErrorHandler();

    public slots:
        void handleLowBattery();
        void handlePumpFailure();
        void handlePowerFailure();
        void handleLowInsulin();
        void handleLowGlucose();
        void handleHighGlucose();
        void handleNoInsulin();

    signals:
        void increaseInsulin();
        void decreateInsulin();

    private:
        DeliveryHistory* delivery_history;
        bool lowGlucoseShown = false;
        bool highGlucoseShown = false;
        bool lowInsulinShown = false;
        bool noInsulinShown = false;
};

#endif //ERRORHANDLER_H
