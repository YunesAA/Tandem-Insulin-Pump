#include "DeliveryHistory.h"

DeliveryHistory::DeliveryHistory(QObject* parent): QObject(parent) {
    lastCGMTime = QDateTime::currentDateTime();
}

DeliveryHistory::~DeliveryHistory() {
    if (!events.empty()) {
        qDeleteAll(events);
    }

    events.clear();

    if (!errors.empty()) {
        qDeleteAll(errors);
    }

    errors.clear();

    if (!cgmData.empty()) {
        for (auto it = cgmData.begin(); it != cgmData.end(); ++it) {
            delete it.key();
        }
    }

    cgmData.clear();
}

QList<DeliveryEvent*> DeliveryHistory::getEvents() const {
    if (!events.isEmpty()) {
        return events;
    }

    return QList<DeliveryEvent*>();
}

QList<DeliveryError*> DeliveryHistory::getErrors() const {
    if (!errors.isEmpty()) {
        return errors;
    }

    return QList<DeliveryError*>();
}

QMap<QDateTime*, qreal> DeliveryHistory::getCGMData() const {
    if (!cgmData.isEmpty()) {
        return cgmData;
    }

    return QMap<QDateTime*, qreal>();
}

void DeliveryHistory::addEvent(DeliveryEvent* event) {
    events.append(event);
}

void DeliveryHistory::addError(DeliveryError* error) {
    errors.append(error);
}

void DeliveryHistory::addCGMDatum(QDateTime* time, qreal datum) {
    cgmData.insert(time, datum);
}

void DeliveryHistory::addEventSlot(double bolusDose, QDateTime& time) {
    // qDebug()<<"Recieved bolus calcualtion signal: "<< bolusDose;
    DeliveryEvent* event = new DeliveryEvent(bolusDose, time);
    events.append(event);
    emit newDataAddedSignal();
}

void DeliveryHistory::addErrorSlot(DeliveryError* error) {
    // qDebug()<<"Recieved error signal";
    errors.append(error);
    emit newDataAddedSignal();
}

void DeliveryHistory::addCGMDatumSlot(double reading) {
    lastCGMTime = lastCGMTime.addSecs(60 * 5);
    QDateTime* time = new QDateTime(lastCGMTime);
    cgmData.insert(time, reading);
    emit newDataAddedSignal();
}

void DeliveryHistory::addTestData() {
    addCGMDatum(new QDateTime(QDateTime::currentDateTime()), 0.0);
    addCGMDatum(new QDateTime(QDateTime::currentDateTime().addSecs(60)), 0.1);
    addCGMDatum(new QDateTime(QDateTime::currentDateTime().addSecs(120)), 0.2);
    addError(new DeliveryError(LOW_BATTERY));
    addError(new DeliveryError(HIGH_GLUCOSE));
    addError(new DeliveryError(PUMP_FAILURE));
    QDateTime* time = new QDateTime(QDateTime::currentDateTime());
    addEvent(new DeliveryEvent(0.0, *time));
    addEvent(new DeliveryEvent(0.1, *time));
    addEvent(new DeliveryEvent(0.2, *time));
}
