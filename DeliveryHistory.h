// Stores history of insulin delivery, CGM history, and errors
#ifndef DELIVERYHISTORY_H
#define DELIVERYHISTORY_H

#include <QObject>
#include <QList>
#include "DeliveryError.h"
#include "DeliveryEvent.h"

class DeliveryHistory : public QObject {
        Q_OBJECT

    public:
        explicit DeliveryHistory(QObject* parent = nullptr);
        ~DeliveryHistory();

        QList<DeliveryEvent*> getEvents() const;
        QList<DeliveryError*> getErrors() const ;
        QMap<QDateTime*, qreal> getCGMData() const;
        void addTestData();

        void addEvent(DeliveryEvent* event);
        void addError(DeliveryError* error);
        void addCGMDatum(QDateTime* time, qreal datum);

    public slots:
        void addEventSlot(double bolusDose, QDateTime& time);
        void addErrorSlot(DeliveryError* error);
        void addCGMDatumSlot(double reading);

    private:
        QDateTime lastCGMTime;
        QList<DeliveryEvent*> events;
        QList<DeliveryError*> errors;
        QMap<QDateTime*, qreal> cgmData;

    signals:
        void newDataAddedSignal();
};

#endif //DELIVERYHISTORY_H
