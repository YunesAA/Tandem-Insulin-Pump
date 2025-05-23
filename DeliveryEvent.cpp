#include "DeliveryEvent.h"

DeliveryEvent::DeliveryEvent(float bolus, QDateTime& time): timestamp(time), bolus(bolus){}

DeliveryEvent::~DeliveryEvent() {}

float DeliveryEvent::get_bolus(){
    return bolus;
}

QDateTime DeliveryEvent::get_timestamp(){
    return timestamp;
}
