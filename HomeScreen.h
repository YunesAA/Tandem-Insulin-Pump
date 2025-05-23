#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include "BasePumpScreen.h"
#include "InsulinGauge.h"
#include "DeliveryHistory.h"
#include "DataGraph.h"

namespace Ui {
    class HomeScreen;
}

class HomeScreen : public BasePumpScreen {
        Q_OBJECT

    public:
        explicit HomeScreen(QWidget* parent = nullptr);
        ~HomeScreen();
        InsulinGauge* getGauge() const;

    public:
        void setDeliveryHistory(DeliveryHistory* history);

    signals:
        void optionsButtonClicked();
        void bolusButtonClicked();

    private slots:
        void navigateToOptions();
        void navigateToBolus();

    private:
        Ui::HomeScreen* ui;
        DeliveryHistory* deliveryHistory;
        DataGraph* dataGraph;
};

#endif // HOMESCREEN_H
