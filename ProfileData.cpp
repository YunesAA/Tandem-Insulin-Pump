#include "ProfileData.h"

ProfileData::ProfileData(QWidget* parent, const QString& proName) : QPushButton(proName, parent) {
    name = proName;
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    connect(this, &QPushButton::clicked, this, &ProfileData::openActions);
    timer = new QTimer(this);
    timer->start(1000);
}

QString ProfileData::getName() const {
    return name;
}

void ProfileData::setName(const QString& newName) {
    setText(newName);
    name = newName;
}

QTime ProfileData::getInsulinDuration() const {
    return insulinDuration;
}

void ProfileData::setInsulinDuration(const QTime& newInsulinDuration) {
    insulinDuration = newInsulinDuration;
}

void ProfileData::addTimedSetting(TimedSetting* newTimedSetting) {
    timedSettings += newTimedSetting;
}

void ProfileData::deleteTimedSetting(int index) {}

void ProfileData::openActions() {
    emit profileClicked(this);
}

bool ProfileData::isActive() const {
    return active;
}

TimedSetting* ProfileData::getCurrentTimedSetting() const {
    QDateTime* date = new QDateTime(QDateTime::currentDateTime());
    TimedSetting* closest = timedSettings[0];

    for (TimedSetting* set : timedSettings) {
        if (*set->getTime() < date->time() && set->getTime() > closest->getTime()) {
            closest = set;
        }
    }

    delete date;
    return closest;
}

float ProfileData::getCurrentBasalRate() const {
    return getCurrentTimedSetting()->getBasalRate();
}

float ProfileData::getCurrentCarbRatio() const {
    return getCurrentTimedSetting()->getCarbRatio();
}

float ProfileData::getCurrentCorrectionFactor() const {
    return getCurrentTimedSetting()->getCorrectionFactor();
}

float ProfileData::getCurrentTargetGlucose() const {
    return getCurrentTimedSetting()->getTargetGlucose();
}

void ProfileData::setActive(bool newActive) {
    if (active == newActive) return;

    active = newActive;

    if (newActive) emit activated();
}

QList<TimedSetting*> ProfileData::getTimedSettings() const {
    return timedSettings;
}

bool ProfileData::getCarbs() const {
    return carbs;
}

void ProfileData::setCarbs(bool newCarbs) {
    carbs = newCarbs;
}
