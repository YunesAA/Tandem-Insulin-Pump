#ifndef PUMPTIMER_H
#define PUMPTIMER_H

#include <QObject>
#include <QTimer>

class PumpTimer: public QObject {
        Q_OBJECT

    public:
        explicit PumpTimer(QObject* parent = nullptr);
        QTimer* getTimer() const;

    private:
        QTimer* timer;

    signals:
        void measureGlucose();
};

#endif // PUMPTIMER_H
