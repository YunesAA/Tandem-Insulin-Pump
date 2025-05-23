#include "TimedSetting.h"
#include "ui_TimedSettingButton.h"

TimedSetting::TimedSetting(QWidget* parent) : QPushButton(parent), ui(new Ui::TimedSettingButton) {
    ui->setupUi(this);
}

TimedSetting::TimedSetting(QTime* time, float basalRate, float carbRatio, float correctionFactor, float targetGlucose) {
    TimedSetting();
    this->time = time;
    this->basalRate = basalRate;
    this->carbRatio = carbRatio;
    this->correctionFactor = correctionFactor;
    this->targetGlucose = targetGlucose;
}

TimedSetting::TimedSetting(const TimedSetting& other) {
    TimedSetting();
    this->time = new QTime(*other.time);
    this->basalRate = other.basalRate;
    this->carbRatio = other.carbRatio;
    this->correctionFactor = other.correctionFactor;
    this->targetGlucose = other.targetGlucose;
}

TimedSetting::~TimedSetting() {
    // delete time;
    delete ui;
}

QTime* TimedSetting::getTime() const {
    return time;
}

void TimedSetting::setTime(QTime* newTime) {
    time = newTime;
}

float TimedSetting::getBasalRate() const {
    return basalRate;
}

void TimedSetting::setBasalRate(float newBasalRate) {
    basalRate = newBasalRate;
}

float TimedSetting::getCarbRatio() const {
    return carbRatio;
}

void TimedSetting::setCarbRatio(float newCarbRatio) {
    carbRatio = newCarbRatio;
}

float TimedSetting::getCorrectionFactor() const {
    return correctionFactor;
}

void TimedSetting::setCorrectionFactor(float newCorrectionFactor) {
    correctionFactor = newCorrectionFactor;
}

float TimedSetting::getTargetGlucose() const {
    return targetGlucose;
}

QSize TimedSetting::sizeHint() const {
    int basa = std::max(ui->basalText->sizeHint().width(), ui->basalValue->sizeHint().width());
    int corr = std::max(ui->correctionText->sizeHint().width(), ui->correctionValue->sizeHint().width());
    int carb = std::max(ui->carbText->sizeHint().width(), ui->carbValue->sizeHint().width());
    int targ = std::max(ui->targetText->sizeHint().width(), ui->targetValue->sizeHint().width());
    int width = basa + corr + carb + targ + 32;
    int time = ui->timeEdit->sizeHint().height();
    int text = ui->targetText->sizeHint().height();
    int value = ui->basalValue->sizeHint().height();
    int height = time + text + value + 6;
    return QSize(width, height);
}

void TimedSetting::setTargetGlucose(float newTargetGlucose) {
    targetGlucose = newTargetGlucose;
}

void TimedSetting::openEditor() {
    emit timedSettingClicked(this);
}
