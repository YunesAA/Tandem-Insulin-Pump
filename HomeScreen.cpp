#include "HomeScreen.h"
#include "ui_HomeScreen.h"

HomeScreen::HomeScreen(QWidget* parent) : BasePumpScreen(parent, ""),
    ui(new Ui::HomeScreen),
    deliveryHistory(nullptr),
    dataGraph(nullptr) {
    ui->setupUi(this);
    connect(ui->graphWindowSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        if (!dataGraph) return;

        switch (index) {
            case 0:
                dataGraph->setWindowMinutes(60);   // 1 hour
                break;

            case 1:
                dataGraph->setWindowMinutes(180);  // 3 hours
                break;

            case 2:
                dataGraph->setWindowMinutes(360);  // 6 hours
                break;

            default:
                break;
        }
    });
}

HomeScreen::~HomeScreen() {
    delete ui;
}

void HomeScreen::setDeliveryHistory(DeliveryHistory* history) {
    deliveryHistory = history;

    if (dataGraph) {
        delete dataGraph;
    }

    dataGraph = new DataGraph(deliveryHistory, this);
    QVBoxLayout* layout = new QVBoxLayout(ui->graphWidget);
    layout->addWidget(dataGraph);
    ui->graphWidget->setLayout(layout);
}

InsulinGauge* HomeScreen::getGauge() const {
    return ui->InsulinGaugeWidget;
}

void HomeScreen::navigateToOptions() {
    emit optionsButtonClicked();
}

void HomeScreen::navigateToBolus() {
    emit bolusButtonClicked();
}

REGISTER_DERIVED_TYPE(HomeScreen);
