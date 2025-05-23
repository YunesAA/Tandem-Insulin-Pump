#include "HistoryScreen.h"
#include <QDebug>
#include "ui_HistoryScreen.h"

HistoryScreen::HistoryScreen(QWidget* parent, DeliveryHistory* history)
    : BasePumpScreen(parent, "History", true, true), ui(new Ui::HistoryScreen), deliveryHistory(history) {
    ui->setupUi(this);
    // qDebug() << "Delivery history pointer: " << deliveryHistory;
    ui->verticalLayout->insertWidget(0, buttonBar);
    connect(ui->dataOptionsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            &HistoryScreen::onComboOptionPicked);
    ui->dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

HistoryScreen::~HistoryScreen() {
    delete ui;
    delete deliveryHistory;
}

void HistoryScreen::setDeliveryHistory(DeliveryHistory* history) {
    this->deliveryHistory = history;
}

void HistoryScreen::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    static bool firstTime = true;

    if (firstTime) {
        onComboOptionPicked(0);
        firstTime = false;
    }
}

void HistoryScreen::updateNewData(){
    updateTableData(ui->dataOptionsComboBox->currentIndex());
}

void HistoryScreen::updateTableData(int index){
    ui->dataTable->horizontalHeaderItem(1)->setText("Details");
    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);

    switch (index) {
    case 0: {
        // CGM readings
        ui->dataTable->horizontalHeaderItem(1)->setText("CGM Reading (mmol/L)");

        if (!deliveryHistory) {
            qDebug() << "Delivery history pointer does not exist.";
            break;
        }

        auto cgmMap = deliveryHistory->getCGMData();

        QList<QPair<QDateTime, qreal>> sortedCGM;
        for (auto it = cgmMap.begin(); it != cgmMap.end(); ++it) {
            if (it.key()) {
                sortedCGM.append(qMakePair(*it.key(), it.value()));
            }
        }

        std::sort(sortedCGM.begin(), sortedCGM.end(),
                  [](const QPair<QDateTime, qreal>& a, const QPair<QDateTime, qreal>& b) {
                      return a.first < b.first;
                  });

        for (const auto& entry : sortedCGM) {
            int row = ui->dataTable->rowCount();
            ui->dataTable->insertRow(row);
            ui->dataTable->setItem(row, 0, new QTableWidgetItem("CGM Reading"));
            ui->dataTable->setItem(row, 1, new QTableWidgetItem(QString::number(entry.second)));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(entry.first.toString("yyyy-MM-dd hh:mm:ss")));
        }

        break;
    }

    case 1: {
        // Insulin delivery
        ui->dataTable->horizontalHeaderItem(1)->setText("Insulin Bolus (unit)");

        if (!deliveryHistory) {
            qDebug() << "Delivery history pointer does not exist.";
            break;
        }

        QList<DeliveryEvent*> list = deliveryHistory->getEvents();

        for (qsizetype i = 0; i < list.size(); ++i) {
            int row = ui->dataTable->rowCount();
            ui->dataTable->insertRow(row);
            ui->dataTable->setItem(row, 0, new QTableWidgetItem("Insulin Delivery"));
            ui->dataTable->setItem(row, 1, new QTableWidgetItem(QString::number(list.at(i)->get_bolus())));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(list.at(i)->get_timestamp().toString("yyyy-MM-dd hh:mm:ss")));
        }

        break;
    }

    case 2: {
        // Error event
        ui->dataTable->horizontalHeaderItem(1)->setText("Alert Type");

        if (!deliveryHistory) {
            qDebug() << "Delivery history pointer does not exist.";
            break;
        }

        QList<DeliveryError*> list = deliveryHistory->getErrors();

        for (qsizetype i = 0; i < list.size(); ++i) {
            int row = ui->dataTable->rowCount();
            ui->dataTable->insertRow(row);
            ui->dataTable->setItem(row, 0, new QTableWidgetItem("Alert Event"));
            ui->dataTable->setItem(row, 1, new QTableWidgetItem(list.at(i)->get_error_string()));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(list.at(i)->get_timestamp().toString("yyyy-MM-dd hh:mm:ss")));
        }

        break;
    }

    default:

        ui->dataTable->horizontalHeaderItem(1)->setText("CGM Reading (mmol/L)");

        if (!deliveryHistory) {
            qDebug() << "Delivery history pointer does not exist.";
            break;
        }

        auto cgmMap = deliveryHistory->getCGMData();

        QList<QPair<QDateTime, qreal>> sortedCGM;
        for (auto it = cgmMap.begin(); it != cgmMap.end(); ++it) {
            if (it.key()) {
                sortedCGM.append(qMakePair(*it.key(), it.value()));
            }
        }

        std::sort(sortedCGM.begin(), sortedCGM.end(),
                  [](const QPair<QDateTime, qreal>& a, const QPair<QDateTime, qreal>& b) {
                      return a.first < b.first;
                  });

        for (const auto& entry : sortedCGM) {
            int row = ui->dataTable->rowCount();
            ui->dataTable->insertRow(row);
            ui->dataTable->setItem(row, 0, new QTableWidgetItem("CGM Reading"));
            ui->dataTable->setItem(row, 1, new QTableWidgetItem(QString::number(entry.second)));
            ui->dataTable->setItem(row, 2, new QTableWidgetItem(entry.first.toString("yyyy-MM-dd hh:mm:ss")));
        }
        break;
    }
}

//Fills table in history screen with data based on the index of the drop down menu picked (on combo option picked)
void HistoryScreen::onComboOptionPicked(int index) {
    updateTableData(index);
}

REGISTER_DERIVED_TYPE(HistoryScreen);
