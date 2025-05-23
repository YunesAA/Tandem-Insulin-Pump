//Home screen displaying insulin delivery, battery, CGM data, and navigation buttons.
#ifndef PUMPWINDOW_H
#define PUMPWINDOW_H

#include <QFinalState>
#include <QMainWindow>
#include <QStateMachine>
#include <QHistoryState>
#include <QState>
#include "BasePumpScreen.h"
#include "DeliveryHistory.h"
#include "BatteryIndicator.h"
#include "InsulinGauge.h"

namespace Ui {
    class PumpWindow;
}

class PumpWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit PumpWindow(QWidget* parent = nullptr, DeliveryHistory* delivery_history = nullptr);
        ~PumpWindow();

        void gotoLastScreen();
        void gotoHomeScreen();
        void gotoNextScreen();

        template<typename T> T* getScreen();
        template<typename T> QState* getState();

        template<typename T, typename F, typename... SignalArgs, typename... SlotArgs>
        void addCircularTransition(void (F::*signal)(SignalArgs...), void (T::*slot)(SlotArgs...) = nullptr) {
            getState<F>()->addTransition(getScreen<F>(), signal, getState<T>());
            getState<T>()->addTransition(getScreen<T>(), &T::backClicked, getState<F>());
            getState<T>()->addTransition(getScreen<T>(), &T::confirmed, getState<F>());

            if (slot) connect(getScreen<F>(), signal, getScreen<T>(), slot);
        }

    private slots:
        void onBatteryCharged();
        void onRefillInsulin();

    private:
        Ui::PumpWindow* ui;
        QMap<BasePumpScreen*, QState*> screenStateMap;
        DeliveryHistory* deliveryHistory;
        QStateMachine* screenStateMachine;
        QHistoryState* history;
        QState* mainState;
        BatteryIndicator* batteryIndicator;
        InsulinGauge* insulinGauge;

        void connections();
        void initStateMachine();
        void initAllStates();
        QState* initState(BasePumpScreen* screen);
        void initTransitions();

    signals:
        void refillInsulin(float level);
};

#endif // PUMPWINDOW_H
