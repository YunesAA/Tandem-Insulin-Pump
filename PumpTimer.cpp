#include "PumpTimer.h"

PumpTimer::PumpTimer(QObject* parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PumpTimer::measureGlucose);
    timer->start(1000);
}

QTimer* PumpTimer::getTimer() const {
    return timer;
}
