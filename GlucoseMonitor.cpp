#include "GlucoseMonitor.h"
#include <QDebug>

GlucoseMonitor::GlucoseMonitor(QObject* parent) : QObject{parent} {}

void GlucoseMonitor::measureGlucose() {
    double glucose_reading = 0;

    for (int i = 0; i < activeEvents.size(); ++i) {
        GlucoseEvent &event = activeEvents[i];

        switch (event.getType()) {
            case GlucoseEvent::Meal:
                glucose_reading += event.getMagnitude() * 0.1;
                break;

            case GlucoseEvent::Insulin:
                glucose_reading -= event.getMagnitude() * 0.01;
                break;

            case GlucoseEvent::Exercise:
                glucose_reading -= event.getMagnitude() * 0.01;
                break;
        }

        event.decrementTime();
    }

    activeEvents.erase(std::remove_if(activeEvents.begin(), activeEvents.end(), [](const GlucoseEvent & e) {
        return e.isExpired();
    }), activeEvents.end());

    glucose_reading += (rand() % 5 - 2);
    current_glucose += glucose_reading;
    current_glucose = qBound(40.0, current_glucose, 400.0);

    if (current_glucose > 180) {
        emit handleHighGlucose();
        emit signalBolusCalculator(100, this->current_glucose, 0, 0);
    } else if (current_glucose < 70) {
        emit handleLowGlucose();
    }

    emit signalGlucoseLevel(current_glucose);
}

void GlucoseMonitor::insulinDeliverySlot(double bolus, QDateTime& time) {
    qDebug() << "Recieved insulin event (glucose monitoring)";
    GlucoseEvent insulin_event = { GlucoseEvent::Insulin, bolus, 12};
    activeEvents.append(insulin_event);
}

void GlucoseMonitor::addExerciseEventSlot(double intensity, int minutes) {
    qDebug() << "Recieved exercise event";
    GlucoseEvent exercise_event = { GlucoseEvent::Exercise, intensity, minutes};
    activeEvents.append(exercise_event);
    emit signalInsulinReduction(intensity);
    emit signalInsulinReduction(intensity);

    emit signalInsulinReduction(intensity);
}

void GlucoseMonitor::addMealEventSlot(double carbs) {
    qDebug() << "Recieved meal event";
    GlucoseEvent meal_event = { GlucoseEvent::Meal, carbs, 12};
    activeEvents.append(meal_event);
    emit signalBolusCalculator(carbs, this->current_glucose, 0, 0);
}
