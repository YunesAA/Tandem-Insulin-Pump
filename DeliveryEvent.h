//Data type that stores insulin delivery hisotry. Used in DataLogger.h
#ifndef DELIVERYEVENT_H
#define DELIVERYEVENT_H

#include <QObject>
#include <QDateTime>

class DeliveryEvent {
    public:
        DeliveryEvent(float bolus, QDateTime& time);
        ~DeliveryEvent();
        float get_bolus();
        QDateTime get_timestamp();

    private:
        QDateTime timestamp;
        float bolus;
};

#endif //DELIVERYEVENT_H
