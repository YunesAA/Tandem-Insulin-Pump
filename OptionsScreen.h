#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"

namespace Ui {
    class OptionsScreen;
}

class OptionsScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit OptionsScreen(QWidget* parent = nullptr);
        ~OptionsScreen();

    signals:
        void profileButtonClicked();
        void historyButtonClicked();
        void stopInsulinButtonClicked();
        void startInsulinButtonClicked();

    private slots:
        void navigateToProfiles();
        void navigateToHistory();
        void stopInsulin();

    public slots:
        void onInsulinStopped();
        void onInsulinResumed();

    private:
        Ui::OptionsScreen* ui;
        bool insulinIsBeingDelivered = true;
};

#endif // OPTIONSSCREEN_H
