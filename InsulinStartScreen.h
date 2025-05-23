#ifndef INSULINSTARTSCREEN_H
#define INSULINSTARTSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class InsulinStartScreen;
}

class InsulinStartScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit InsulinStartScreen(QWidget* parent = nullptr);
        ~InsulinStartScreen();

    signals:
        void insulinStartConfirmed();

    private slots:
        void insulinStartConfirmedClicked();

    private:
        Ui::InsulinStartScreen* ui;
};

#endif // INSULINSTARTSCREEN_H
