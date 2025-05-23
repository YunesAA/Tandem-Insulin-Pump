#ifndef DELIVERYERROR_H
#define DELIVERYERROR_H

#include <QObject>
#include <QDateTime>

// Enum data type to differentiate different error types
enum ErrorType {
    PUMP_FAILURE,
    POWER_FAILURE,
    LOW_BATTERY,
    LOW_INSULIN,
    LOW_GLUCOSE,
    HIGH_GLUCOSE,
    NO_INSULIN
};

class DeliveryError {
    public:
        DeliveryError(ErrorType error);
        ~DeliveryError();
        ErrorType get_error_type();
        bool is_resolved();
        QDateTime get_timestamp();
        QString get_error_string();

    private:
        QDateTime timestamp;
        ErrorType error;
        bool resolved;
};

#endif // DELIVERYERROR_H
