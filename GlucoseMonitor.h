#ifndef GLUCOSEMONITOR_H
#define GLUCOSEMONITOR_H

#include <QObject>

class GlucoseEvent {
    public:
        enum Type {Meal, Insulin, Exercise};

        GlucoseEvent(Type type, double magnitude, int duration): event_type(type), magnitude(magnitude), time_remaining(duration) {}

        Type getType() const {
            return event_type;
        }

        double getMagnitude() const {
            return magnitude;
        }

        int timeRemaining() const {
            return time_remaining;
        }

        void decrementTime() {
            time_remaining--;
        }

        bool isExpired() const {
            return time_remaining <= 0;
        }

    private:
        Type event_type;
        double magnitude;
        int time_remaining;
};

class GlucoseMonitor : public QObject {
        Q_OBJECT

    public:
        explicit GlucoseMonitor(QObject* parent = nullptr);

    private:
        double current_glucose = 100.0;
        QList<GlucoseEvent> activeEvents;

    public slots:
        void measureGlucose();
        void insulinDeliverySlot(double bolus, QDateTime& time);
        void addExerciseEventSlot(double intensity, int minutes);
        void addMealEventSlot(double carbs);

    signals:
        void signalGlucoseLevel(double glucose_level);
        void handleLowGlucose();
        void handleHighGlucose();
        void signalBolusCalculator(double carbIntake, double currentBG, int hours, bool extended);
        void signalInsulinReduction(double intensity);
};

#endif // GLUCOSEMONITOR_H
