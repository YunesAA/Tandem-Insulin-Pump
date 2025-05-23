#ifndef ALARMPOPUP_H
#define ALARMPOPUP_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class AlarmPopup;
}

class AlarmPopup : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit AlarmPopup(QWidget* parent = nullptr);
        ~AlarmPopup();

    private:
        Ui::AlarmPopup* ui;
};

#endif // ALARMPOPUP_H
