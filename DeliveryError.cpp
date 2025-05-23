#include "DeliveryError.h"

DeliveryError::DeliveryError(ErrorType error): timestamp(QDateTime::currentDateTime()), error(error) {}

DeliveryError::~DeliveryError() {}

ErrorType DeliveryError::get_error_type(){
    return error;
}

bool DeliveryError::is_resolved(){
    return resolved;
}

QDateTime DeliveryError::get_timestamp(){
    return timestamp;
}

QString DeliveryError::get_error_string(){
    QString message;
    switch (error){
        case PUMP_FAILURE:
            message = "Pump failure";
            break;
        case POWER_FAILURE:
            message = "Power failure";
            break;
        case LOW_BATTERY:
            message = "Low battery";
            break;
        case LOW_INSULIN:
            message = "Low insulin";
            break;
        case LOW_GLUCOSE:
            message = "Low glucose";
            break;
        case HIGH_GLUCOSE:
            message = "High glucose";
            break;

        case NO_INSULIN:
            message = "No Insulin";
            break;
    }

    return message;
}
