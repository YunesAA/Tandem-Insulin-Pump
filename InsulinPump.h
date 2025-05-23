#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include <QObject>
#include "BatteryIndicator.h"
#include "BolusCalculator.h"
#include "DeliveryHistory.h"
#include "ErrorHandler.h"
#include "InsulinReservoir.h"
#include "ProfileData.h"
#include "PumpWindow.h"
#include "BolusScreen.h"
#include "PumpTimer.h"
#include "GlucoseMonitor.h"
#include "ExerciseScreen.h"
#include "HistoryScreen.h"
#include "HomeScreen.h"
#include "MealScreen.h"
#include "DataGraph.h"

class InsulinPump : public QObject {
        Q_OBJECT

    public:
        explicit InsulinPump(QObject* parent = nullptr);
        ~InsulinPump();
        void startSimulation();
        QList<ProfileData*> getUserProfiles() const;
        ProfileData* getActiveProfile() const;
        PumpWindow* getWindow() const;
        DeliveryHistory* getHistory() const;
        BolusCalculator* getBolusCalc() const;
        InsulinReservoir* getReservoir() const;
        BatteryIndicator* getBattery() const;
        ErrorHandler* getErrHandler() const;
        PumpTimer* getTimer() const;
        GlucoseMonitor* getGlucoseMonitor() const;
        DataGraph* getDataGraph() const;

    private:
        DeliveryHistory* history;
        GlucoseMonitor* glucoseMonitor;
        QList<ProfileData*> userProfiles;
        PumpWindow* window;
        BolusCalculator* bolusCalc;
        InsulinReservoir* reservoir;
        BatteryIndicator* battery;
        ErrorHandler* errHandler;
        PumpTimer* timer;
        DataGraph* dataGraph;
        QTimer* mealTimer;
        QTimer* exerciseTimer;
        QTimer* insulinMonitorTimer;
};

#endif // INSULINPUMP_H
