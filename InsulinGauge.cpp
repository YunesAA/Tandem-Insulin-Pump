#include "InsulinGauge.h"
#include "ui_InsulinGauge.h"
#include <QVBoxLayout>

InsulinGauge::InsulinGauge(QWidget* parent)
    : QWidget(parent), ui(new Ui::InsulinGauge) {
    ui->setupUi(this);
    ui->InsulinLevel->setText("Insulin Level: 200 units");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->InsulinLevel);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

InsulinGauge::~InsulinGauge() {
    delete ui;
}

void InsulinGauge::levelChanged(float level) {
    ui->InsulinLevel->setText(QString("Insulin Level: %1 units").arg(level));
}

void InsulinGauge::setInsulinlevel(){
    this->insulinlevel=200;
    levelChanged(insulinlevel);
    qDebug() << "Insulin level set to: " << insulinlevel;
}

