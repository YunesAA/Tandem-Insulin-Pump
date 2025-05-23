#ifndef INSULINRESERVOIR_H
#define INSULINRESERVOIR_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class InsulinReservoir : public QObject {
        Q_OBJECT

        struct ScheduledDose {
            double dose;
            QDateTime& start_time;
            int position;
        };

    public:
        InsulinReservoir();

        void setLevel(float newLevel);
        float getLevel() const;

    public slots:
        void bolusImmediateSlot(double dose, QDateTime& time);
        void bolusExtendedSlot(double dose, QDateTime& time, double delayTime);
        void exerciseInsulinReduction(double intensity);

    signals:
        void levelChanged(float newLevel);
        void addDeliveryHistory(double dose, QDateTime& time);
        void noInsulinSignal();
        void lowInsulin();

    private:
        float level;
        QList<ScheduledDose> extendedDoses;
        QTimer* timer;

    private slots:
        void deliverExtendedBolus();
};

#endif // INSULINRESERVOIR_H
