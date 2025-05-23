#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include "DeliveryHistory.h"
#include "BasePumpScreen.h"
#include <QWidget>

namespace Ui {
    class HistoryScreen;
}

class HistoryScreen : public BasePumpScreen {
        Q_OBJECT
    public:
        explicit HistoryScreen(QWidget* parent = nullptr,
                               DeliveryHistory* deliveryHistory = nullptr);
        ~HistoryScreen();
        void setDeliveryHistory(DeliveryHistory* history);
        void updateTableData(int index);

    public slots:
        void updateNewData();

    private slots:
        void onComboOptionPicked(int index);

    private:
        Ui::HistoryScreen* ui;
        DeliveryHistory* deliveryHistory;

    protected:
        void showEvent(QShowEvent* event) override;
};

#endif // HISTORYSCREEN_H
