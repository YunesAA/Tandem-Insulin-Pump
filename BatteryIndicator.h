#ifndef BATTERYINDICATOR_H
#define BATTERYINDICATOR_H
#include <QWidget>
#include <QTimer>

namespace Ui {
    class BatteryIndicator;
}

class BatteryIndicator : public QWidget {
        Q_OBJECT
    public:
        explicit BatteryIndicator(QWidget* parent = nullptr);
        ~BatteryIndicator();

        void setBatteryLevel(int level);
        void chargeBattery();
        void setPowerOffAction(QAction* action);
        //BatteryIndicator* getBatteryIndicator();

    signals:
        void batteryLow();

    private:
        Ui::BatteryIndicator* ui;
        QTimer* batteryTimer;
        int batteryLevel;
        void updateDisplay(int batteryLevel);
        QAction* powerOffAction;

    private slots:
        void decreaseBattery();

};

#endif // BATTERYINDICATOR_H
