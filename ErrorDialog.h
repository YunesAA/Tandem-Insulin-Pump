#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include "DeliveryError.h"

namespace Ui {
    class ErrorDialog;
}

class ErrorDialog : public QDialog {
        Q_OBJECT

    public:
        explicit ErrorDialog(ErrorType error, QDialog* parent = nullptr);

        ~ErrorDialog();

    private:
        Ui::ErrorDialog* ui;
        void displayError(ErrorType error);
};

#endif // ERRORDIALOG_H
