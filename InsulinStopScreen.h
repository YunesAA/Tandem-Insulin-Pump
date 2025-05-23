#ifndef INSULINSTOPSCREEN_H
#define INSULINSTOPSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class InsulinStopScreen;
}

class InsulinStopScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit InsulinStopScreen(QWidget* parent = nullptr);
        ~InsulinStopScreen();
        void setTimer(int time);
        int getTimer() const;
        void subtractOneMinuteFromTimer();

    signals:
        void insulinStopConfirmed();
        void timerUpdated();

    private slots:
        void insulinStopConfirmedClicked();

    private:
        Ui::InsulinStopScreen* ui;
        int timer; // How many minutes left until user gets a reminder to turn back on their insulin
};

#endif // INSULINSTOPSCREEN_H
